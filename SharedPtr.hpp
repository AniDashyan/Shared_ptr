#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP


template <typename T>
class WeakPtr;

struct ControlBlock {
    unsigned int strong_count;
    unsigned int weak_count;

    ControlBlock() : strong_count(1), weak_count(0) {}
};

template <typename T>
class SharedPtr {
private:
    T* raw_ptr;
    ControlBlock* control_block;

    void release() {
        if (control_block) {
            --(control_block->strong_count);
            if (control_block->strong_count == 0) {
                delete raw_ptr;
                raw_ptr = nullptr;
                if (control_block->weak_count == 0) {
                    delete control_block;
                    control_block = nullptr;
                }
            }
        }
    }

    friend class WeakPtr<T>;

public:
    SharedPtr(T* raw_ptr = nullptr) : raw_ptr(raw_ptr), control_block(raw_ptr ? new ControlBlock() : nullptr) {}

    
    SharedPtr(const SharedPtr& other) : raw_ptr(other.raw_ptr), control_block(other.control_block) {
        if (control_block) ++(control_block->strong_count);
    }

    ~SharedPtr() {
        release();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            raw_ptr = other.raw_ptr;
            control_block = other.control_block;
            if (control_block) 
                ++(control_block->strong_count);
        }
        return *this;
    }

    void reset(T* raw_ptr = nullptr) {
        release();
        this->raw_ptr = raw_ptr;
        control_block = raw_ptr ? new ControlBlock() : nullptr;
    }

    void swap(SharedPtr& other) {
        std::swap(raw_ptr, other.raw_ptr);
        std::swap(control_block, other.control_block);
    }

    T* get() const {
        return raw_ptr;
    }

    T& operator*() const {
        return *raw_ptr;
    }

    T* operator->() const {
        return raw_ptr;
    }

    T& operator[](size_t index) const {
        return raw_ptr[index];
    }

    long use_count() const {
        return control_block ? control_block->strong_count : 0;
    }

    bool unique() const {
        return control_block ? (control_block->strong_count == 1) : true;
    }

};

template <typename T>
class WeakPtr {
private:
    T* raw_ptr;
    ControlBlock* control_block;

    void release() {
        if (control_block) {
            --(control_block->weak_count);
            if (control_block->weak_count == 0 && control_block->strong_count == 0) {
                delete control_block;
                control_block = nullptr;
            }
        }
    }

public:
    WeakPtr() : raw_ptr(nullptr), control_block(nullptr) {}

    WeakPtr(const SharedPtr<T>& shared_ptr) : raw_ptr(shared_ptr.raw_ptr), control_block(shared_ptr.control_block) {
        if (control_block) ++(control_block->weak_count);
    }

    WeakPtr(const WeakPtr& other) : raw_ptr(other.raw_ptr), control_block(other.control_block) {
        if (control_block) ++(control_block->weak_count);
    }

    ~WeakPtr() {
        release();
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            raw_ptr = other.raw_ptr;
            control_block = other.control_block;
            if (control_block) ++(control_block->weak_count);
        }
        return *this;
    }

    WeakPtr& operator=(const SharedPtr<T>& shared_ptr) {
        release();
        raw_ptr = shared_ptr.raw_ptr;
        control_block = shared_ptr.control_block;
        if (control_block) ++(control_block->weak_count);
        return *this;
    }

    bool expired() const {
        return control_block ? (control_block->strong_count == 0) : true;
    }

    // Lock to create a SharedPtr
    SharedPtr<T> lock() const {
        if (expired()) {
            return SharedPtr<T>();
        }
        SharedPtr<T> shared_ptr;
        shared_ptr.raw_ptr = raw_ptr;
        shared_ptr.control_block = control_block;
        ++(control_block->strong_count);
        return shared_ptr;
    }
};

#endif
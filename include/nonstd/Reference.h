//
//  lib/Reference.h - nonstd::reference
//

#pragma once

struct Indexable {
    virtual operator size_t () = 0;
    virtual size_t getIndex() = 0;
};

struct Index : public virtual Indexable {
    Index() = delete;
    Index(size_t index) : index(index) {}

    virtual operator size_t () { return index; }
    virtual size_t getIndex() { return index; }
protected:
    size_t index;
};

template <typename T>
struct Reference {
    Reference() = delete;
    Reference(T* ref) : ref(ref) {}

    operator T* () { return ref; }
    operator T () { return *ref; }
protected:
    T* ref;
};

// End lib/Reference.h


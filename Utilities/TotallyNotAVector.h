//
// Created by Jason Torrence on 11/1/2019.
//
// This was designed in place of the "Vector" class, as the use
// of the vector class was disallowed. The professor didn't mind
// if I made this class.
//
// Feel free to use this in any way you please as long as
// these comments are left alone.
//


#ifndef REAL_ESTATE_TYCOON_TOTALLYNOTAVECTOR_H
#define REAL_ESTATE_TYCOON_TOTALLYNOTAVECTOR_H

template <class e>
class TotallyNotAVector{
protected:
    void CopyAllElements(e* orig, int origL, e* copy, int copyL){
        if(origL>copyL){
            return;
        }
        for(int i = 0; i < origL; i++){
            copy[i] = orig[i];
        }
    }

    void CopyAllButOneElement(e* orig, int origL, e* copy, int copyL, int index){
        if(origL>copyL){
            return;
        }
        for(int i = 0, j = 0; i < origL; i++, j++){
            if(i != index){
                copy[j] = orig[i];
            }else{
                j--;
            }
        }
    }

    int buffer;
    int size;
    e* NotAVector;

public:
    TotallyNotAVector();
    TotallyNotAVector(e* eArray, int size){
        NotAVector = eArray;
        this->size = size;
        buffer = 100;
        while(size > buffer){
            buffer *= 2;
        }
    }
    ~TotallyNotAVector();

    void append(e anotherElement){
        if(size+1 < buffer) {
            NotAVector[size] = anotherElement;
        }else{
            buffer *= 2;
            e* newNotAVector = new e[buffer];
            CopyAllElements(NotAVector, size, newNotAVector, buffer);
            delete[] NotAVector;
            NotAVector = newNotAVector;
        }
        size++;
    }

    e remove(){
        e* newNotAVector = new e[buffer];
        e copyOfRemovedElement = NotAVector[size-1];
        CopyAllElements(NotAVector, size - 1, newNotAVector, buffer);
        delete[] NotAVector;
        NotAVector = newNotAVector;
        size--;
        return copyOfRemovedElement;
    }

    e remove(int index){
        e* newNotAVector = new e[buffer];
        e copyOfRemovedElement = NotAVector[index];
        CopyAllButOneElement(NotAVector, size, newNotAVector, buffer, index);
        delete[] NotAVector;
        NotAVector = newNotAVector;
        size--;
        return copyOfRemovedElement;
    }

    int length(){
        return size;
    }

    e get(int index){
        return NotAVector[index];
    }

    e* getReference(int index){
        return &NotAVector[index];
    }

    void clear(){
        delete[] NotAVector;
        delete &NotAVector;
        NotAVector = new e[buffer];
    }
};

template<class e>
TotallyNotAVector<e>::~TotallyNotAVector(){
    delete[] NotAVector;
    delete &NotAVector;
};

template<class e>
TotallyNotAVector<e>::TotallyNotAVector(){
    buffer = 100;
    size = 0;
    NotAVector = new e[buffer];
};

#endif //REAL_ESTATE_TYCOON_TOTALLYNOTAVECTOR_H

#include<bits/stdc++.h>
using namespace std;


class Dice{
    // 0
    //1234
    // 5
    //top:0, front:2, x:13, y:24, z:50
    static const int N=6;
    int A[N];
public:
    Dice(const vector<int> v1){
        assert(v1.size()>=N);
        for(int i=0;i<N;i++){
            A[i]=v1[i];
        }
    }

    //rotate: clockwise
    void rotateX(){//0->2->5->4->0
        swap(A[0],A[4]);
        swap(A[4],A[5]);
        swap(A[5],A[2]);
    }

    void rotateXrev(){
        swap(A[5],A[2]);
        swap(A[4],A[5]);
        swap(A[0],A[4]);
    }

    void rotateY(){//0->3->5->1
        swap(A[0],A[1]);
        swap(A[1],A[5]);
        swap(A[5],A[3]);
    }

    void rotateYrev(){
        swap(A[5],A[3]);
        swap(A[1],A[5]);
        swap(A[0],A[1]);
    }

    void rotateZ(){//1->2->3->4
        swap(A[4],A[3]);
        swap(A[3],A[2]);
        swap(A[2],A[1]);
    }

    void rotateZrev(){
        swap(A[2],A[1]);
        swap(A[3],A[2]);
        swap(A[4],A[3]);
    }
    
    template<typename T> T hash(int base){
        T s=0;
        for(int i=0;i<N;i++){
            s*=base;
            s+=A[i];
        }
        return s;
    }

    template<typename T> vector<T> all_hash(int base){
        int i,j;
        vector<T> vs;
        const int M=4;
        for(i=0;i<2*M;i++){
            if(i<M)rotateX();
            else rotateY();
            if(i>=M && i%2)continue;
            for(j=0;j<4;j++){
                rotateZ();
                vs.push_back(hash<T>(base));
            }
        }
        return vs;
    }
};

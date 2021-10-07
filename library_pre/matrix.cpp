template<typename type> class Matrix{
public:
    vector<vector<type>> vec_matrix;
private:
    void init(int n){
        vec_matrix.assign(n,vector<type>(n,0));
    }
public:
    Matrix(int n){
        init(n);
    }
    Matrix(vector<vector<type>> ma):vec_matrix(ma){};

    bool valid() const{
        int n=size();
        assert(n>0 && (int)vec_matrix[0].size()==n);
        if(n>0 && (int)vec_matrix[0].size()==n)return true;
        else return false;
    }

    void E(){
        valid();
        for(int i=0;i<size();i++){
            vec_matrix[i][i]=1;
        }
    }
    void E(int n){
        init(n);
        E();
    }

    int size() const{
        return vec_matrix.size();
    }

    Matrix& operator += (const Matrix& matrix_a){
        const vector<vector<type>>& vec_matrix_a=matrix_a.vec_matrix;
        valid(),matrix_a.valid();
        int i,j;
        int n=size();
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                vec_matrix[i][j]+=vec_matrix_a[i][j];
            }
        }
        return *this;
    }

    Matrix& operator *= (const Matrix& matrix_a){
        const vector<vector<type>>& vec_matrix_a=matrix_a.vec_matrix;
        valid(),matrix_a.valid();
        int i,j,k;
        int n=size();
        vector<vector<type>> vec_matrix_b(n,vector<type>(n,0));
        for(i=0;i<n;i++){
            for(k=0;k<n;k++){
                for(j=0;j<n;j++){
                    vec_matrix_b[i][j]+=vec_matrix[i][k]*vec_matrix_a[k][j];					
                }
            }
        }
        vec_matrix=vec_matrix_b;
        return *this;
    }

    Matrix operator +(const Matrix& matrix_a){
        Matrix matrix_s=*this;
        matrix_s+=matrix_a;
        return matrix_s;
    }

    Matrix operator *(const Matrix& matrix_a){
        Matrix matrix_s=*this;
        matrix_s*=matrix_a;
        return matrix_s;
    }

    Matrix pow(Matrix& ma,long long int m){
        long long int p_b=1;
        Matrix<type> ms(ma.size());
        ms.E();
        for(;p_b<=m;p_b<<=1);
        for(p_b>>=1;p_b>0;p_b>>=1){
            ms*=ms;
            if(m&p_b)ms*=ma;
        }
        return ms;
    }
    Matrix& pow(long long int m){
        (*this)=pow((*this),m);
        return *this;
    }

    type get_matrix_element(int a,int b) const{
        assert(a<size() && b<size());
        return vec_matrix[a][b];
    }
};
template<typename T>
T** initMatrix(int sizeMatrix, int size, T** matrix)
{
        int constValue = 0;
        T** tmp = new T*[2*sizeMatrix];

        for(int i = 0; i < 2*sizeMatrix; i++) {
                tmp[i] = new T[2*sizeMatrix];
        }

        for(int i = 0; i < 2*sizeMatrix; i++) {
                for(int j = 0; j < 2*sizeMatrix; j++) {

                        if(i >= sizeMatrix && j < sizeMatrix) {
                                constValue = 3;
                        } else if (j >= sizeMatrix && i < sizeMatrix) {
                                constValue = 2;
                        } else if (j >= sizeMatrix && i >= sizeMatrix ) {
                                constValue = 1;
                        } else {
                                constValue = 0;
                        }
                        if (sizeMatrix > 1) {
                                tmp[i][j] = 4*matrix[i%sizeMatrix][j%sizeMatrix] + constValue;
                        } else
                                tmp[i][j] =  constValue;
                        }
        }

        if (sizeMatrix > 1) {
                for(int i = 0 ; i < sizeMatrix; i++) {
                        delete matrix[i];
                }
                delete matrix;
        }

        if (size > 1) {
                initMatrix(2*sizeMatrix, size-1, tmp);
        } else {
                return tmp;
        }
}

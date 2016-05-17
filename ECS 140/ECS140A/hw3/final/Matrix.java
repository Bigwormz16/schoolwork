//part 5
class Matrix extends Sequence {
	// private Sequence content;
	// 
	// constructor for creating a matrix of specific number of rows and columns
	private int rowsize, colsize;

	public Matrix(int rowsize, int colsize){
		//fill out the sequence
		for(int i = 0; i < rowsize * colsize; i++){
			//link a bunch of MyInts together
			this.add(new MyInteger(), 0);
		}

		this.rowsize = rowsize;
		this.colsize = colsize;
	}

	public void Set(int row, int col, int value){
		//set the value of an element
		//row * colsize + column
		//[0, 0] -> postion 0
		//[1, 1] -> 1*colsize + 1 -> 
		Sequence iter = this;
		int position = (row*colsize) + col;
		for(int i = 0; i < position; i++){
			iter = iter.next;
		}

		//iter now at [row][col], set the value
		((MyInteger)iter.content).Set(value);
	}

	public int Get(int row, int col){
		//get the value of an element
		Sequence iter = this;
		int position = (row*colsize) + col;
		for(int i = 0; i < position; i++){
			iter = iter.next;
		}

		//iter now at [row][col], grab the value
		return ((MyInteger)iter.content).Get();
	}

	public Matrix Sum(Matrix mat){
		//return the sum of two matrices: mat & this

		//assert that matrices have same bounds
		if(this.rowsize != mat.rowsize || this.colsize != mat.colsize){
			System.err.println("Error: matrix size mismatch!");
			System.exit(-1);
		}

		//item to be returned
		Matrix sumMatrix = new Matrix(this.rowsize, this.colsize);
		Sequence sumIter = sumMatrix; //iterator to set values

		SequenceIterator mat1 = this.begin(),
						 mat2 = mat.begin();

		for(int i = 0; i < this.length(); i++){
			//sum = mat1 value + mat2 value
			//(Get() called twice, second time grabs int from MyInteger)
			//todo: fix this disgusting mess - generic abstract in element class
			((MyInteger)sumIter.content).Set(((MyInteger)mat1.get()).Get() + ((MyInteger)mat2.get()).Get());

			//advance all the iterators
			sumIter = sumIter.next;
			mat1.advance();
			mat2.advance();
		}

		return sumMatrix;
	}

	public Matrix Product(Matrix mat){
		//return the product of two matrices: mat & this
		if(this.colsize != mat.rowsize){
			System.out.println("Matrix dimensions incompatible for Product");
			System.exit(-1);
		}

		int result = 0; //holds the sum of products

		Matrix prodMatrix = new Matrix(this.rowsize, mat.colsize);
		//dot product: new dimensions = rows from first matrix, columns from 2nd
		//i = row, j = column -> mult elements of each row by elements of each column
		for(int i = 0; i < this.rowsize; i++){
			//add upp
			for(int j = 0; j < mat.colsize; j++){
				//element in row * element in column
				//add up row_element * col_element
				result = 0;
				for(int k = 0; k < this.colsize; k++){
					/*int a = this.Get(i, k); <-- fixed row for 1st matrix
					int b = mat.Get(k, j);    <-- fixed column for 2nd matrix */
					int a = this.Get(i, k);
					int b =  mat.Get(k, j);
					//System.err.println("Multiplying " + a + " by " + b + " = " + (a*b));
					result = result + (a * b);
				}

				prodMatrix.Set(i, j, result); //set result
				//result = 0; //clear the sum for next calculation
			}
		}

		return prodMatrix;
	} //end product

	@Override
	public void Print(){
		//print the elements of matrix
		for(int row = 0; row < rowsize; row++){
			System.out.print("[ "); //begin with a bracket
			for(int col = 0; col < colsize; col++){
				//value separated by spaces
				System.out.print(this.Get(row, col) + " ");
			}
			System.out.println("]"); //end of row
		}
	} //end of print

} //end of Matrix
class Main {
	public static void main(String[] args){
		System.out.println("Successfully compiled!");
		
		//test classes
		MyChar a = new MyChar('a');
		MyChar b = new MyChar('b');
		MyChar c = new MyChar('c');
		
		MyInteger t1 = new MyInteger(1);
		MyInteger t2 = new MyInteger(2);
		MyInteger t3 = new MyInteger(3);
		
		Sequence seq = new Sequence();
		seq.add(c, 0);
		seq.add(b, 0);
		seq.add(a, 0);
		
		seq.Print();
		
		Sequence seq2 = new Sequence();
		seq2.add(t3, 0);
		seq2.add(t2, 0);
		seq2.add(t1, 0);
		
		seq2.add(seq, 0);
		
//		seq.add(seq, 0);
		
		System.out.println("a");
		seq.Print();
		
		seq2.Print();
		
		System.out.println("a");
		seq2.flatten().Print();

		Matrix mat;// = genMatrix(3, 5);
		Matrix mat2;// = genMatrix(5, 5);
		mat = genMatrix(3, 5);
		mat2 = genMatrix(5 ,5);

		System.out.println("matrix 1: ");
		mat.Print();

		System.out.println("matrix 2: ");
		mat2.Print();

		//System.out.println("matrix 1 + matrix 2: [should be err]");
		//mat.Sum(mat2).Print();

		mat = genMatrix(5, 5);
		System.out.println("new matrix 1:");
		mat.Print();

		System.out.println("sum of mat1 mat2: ");
		mat.Sum(mat2).Print();

		System.exit(0);
	}

	public static Matrix genMatrix(int row, int col){
		Matrix mat = new Matrix(row, col);

		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				mat.Set(i, j, (i + j));
			}
		}
		return mat;
	}
}
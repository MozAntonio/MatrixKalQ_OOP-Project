/* SquareMatrix.java */

package matrixkalq;

//import java.lang.IllegalArgumentException;
//import java.lang.ArithmeticException


public class SquareMatrix extends DenseMatrix {
		
	//Metodi propri privati:
		private SquareMatrix subMatrix(int rowElem, int colElem, int n) {
			if(n==0)
				n=numRows(); //o: n=numCols();
			
			int i=0, j=0;
			SquareMatrix aux = clone();
			
			for(int r=0; r<n; ++r)
				for(int c=0; c<n; ++c) {
					if((r!=rowElem) && (c!=colElem)) {
						aux.setElem(i, j, getElem(r,c));
						j++;
						
						if(j==n-1) {
							i++;
							j=0;
						}
					}
				}
			
			return aux;
		}
		
		private static double calcDet(SquareMatrix sm, int n) {
			double ris=0;
			
			if(n==1)
				return sm.getElem(0,0);
			
			int sign=1;
			SquareMatrix temp;
			for(int j=0; j<n; ++j) {
				temp = sm.subMatrix(0,j,n);
				ris = ris + (sign * sm.getElem(0,j) * calcDet(temp,n-1));
				sign = sign*(-1);
			}
			
			return ris;
		}
		
	//Costruttori:
		public SquareMatrix(int n, double init) { super(n,n,init); }
		public SquareMatrix(int n) { super(n,n); }
		public SquareMatrix() { this(0); }
		
	//Override:
		public SquareMatrix clone() {
			return (SquareMatrix)super.clone();
		}
	
	//Metodi 'concretizzati':		
		public SquareMatrix sum(MatrixBase m) {
			if(!(m instanceof SquareMatrix))
				throw new IllegalArgumentException("è possibile sommare ad una matrice quadrata solo una matrice quadrata");
			
			if(numRows() != m.numRows())
				throw new IllegalArgumentException("la somma è permessa solo tra matrici quadrate dello stesso ordine");
			
			SquareMatrix aux = clone();
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numRows(); ++j)
					aux.setElem(i, j, (getElem(i,j) + m.getElem(i,j)));
			
			return aux;
		}
		
		public SquareMatrix dif(MatrixBase m) {
			if(!(m instanceof SquareMatrix))
				throw new IllegalArgumentException("è possibile sottrarre ad una matrice quadrata solo una matrice quadrata");
			if(numRows() != m.numRows())
				throw new IllegalArgumentException("la differenza è permessa solo tra matrici quadrate dello stesso ordine");
			return (this.sum(m.sProd(-1)));
		}
		
		public SquareMatrix sProd(double scalar) {
			SquareMatrix aux = clone();
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					aux.setElem(i, j, (getElem(i,j) * scalar));
			
			return aux;
		}
		
		public SquareMatrix trans() {
			SquareMatrix aux = this.clone();
			
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					aux.setElem(j, i, getElem(i,j));
			
			return aux;
		}
		
	//Metodi propri:
		public SquareMatrix prod(SquareMatrix m) {
			if(numRows() != m.numRows())
				throw new IllegalArgumentException("il prodotto è permesso solo tra matrici quadrate dello stesso ordine");
			
			SquareMatrix aux = clone();
			aux.fill(0);
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<m.numCols(); ++j)
					for(int k=0; k<numCols(); ++k)
					aux.setElem(i,j, (aux.getElem(i,j) + (getElem(i,k) * m.getElem(k,j))));
			
			return aux;
		}
		
		public void setIdentity() {
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j) {
					if(i!=j)
						setElem(i,j,0);
					else
						setElem(i,j,1);
				}
		}
		
		public SquareMatrix exp(int pot) {
			if(pot<0)
				throw new ArithmeticException("non è possibile calcolare una potenza negativa");
			
			SquareMatrix aux = clone();
			
			if(pot==0)
				aux.setIdentity();
			
			for(int i=1; i<pot; ++i)
				aux = aux.prod(this);
			
			return aux;
		}
		
		public boolean isInvertible() {
			if(rank() == numCols()) //o: numCols()
				return true;
			else
				return false;
		}
		
		public SquareMatrix inv() {
			if(!isInvertible())
				throw new ArithmeticException("matrice non invertibile");
			
			double determinant = det();
			SquareMatrix aux = clone();
			SquareMatrix adjoint = adj();
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					aux.setElem(i, j, (adjoint.getElem(i,j) / determinant));
			
			return aux;
		}
		
		public SquareMatrix adj() {
			int n = numRows(); //o: numCols()
			SquareMatrix aux = clone();
			
			if(n==1) {
				aux.setElem(0, 0, getElem(0,0));
			}
			else {
				SquareMatrix temp;
				for(int i=0; i<n; ++i)
					for(int j=0; j<n; ++j) {
						temp = subMatrix(i,j,0);
						
						int sign;
						if(((i+j) % 2) == 0)
							sign = 1;
						else
							sign = -1;
						
						aux.setElem(j, i, (sign * calcDet(temp,n-1)));
					}
			}
			
			return aux;
		}
		
		public double det() {
			return calcDet(this, numRows()); //o: numCols()
		}
		
		public double trace() {
			double tr=0;
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					if(i==j)
						tr = tr + getElem(i,j);
			
			return tr;
		}
		
	//Metodi ereditati:
		//	public int numRows();
		//	public int numCols();
		//	public boolean equals(Object obj);
		
		//	public String toString();
		//	public double getElem(int i, int j);
		//	public void setElem(int i, int j, double val);
		//	public void swapRows(int r1, int r2, int fromCol);
		//	public void swapCols(int c1, int c2, int fromRow);
		//	public void print(DataOutputStream os, String separator) throws IOException;
		//	public void load(DataInputStream is) throws EOFException, IOException;
		//	public int rank();
		//	public void fill(double val);
		//	public void setRandInt(int from, int to);
		//	public void setRandReal(double from, double to);
		
	//Eccezioni:
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..), swapRows(..), swapCols(..)
		//	NumberFormatException: load(..)
		//	IllegalArgumentException: load(..), setRandInt(..), setRandReal(..)
		//	RuntimeException: clone()
		
		//	ArithmeticException: inv(), exp(..)
		//	IllegalArgumentException: sum(..), dif(..), prod(..)
		//	ArrayIndexOutOfBoundsException: (priv)calcDet(..)
		
} //fine SquareMatrix

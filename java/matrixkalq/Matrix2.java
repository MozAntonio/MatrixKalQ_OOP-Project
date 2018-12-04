/* Matrix2.java */

package matrixkalq;
//import java.lang.IllegalArgumentException;


public class Matrix2 extends SquareMatrix {
	
	//Costruttori:
		public Matrix2(double init) { super(2,init); }
		public Matrix2() { super(2); }
		
	//Override:
		public Matrix2 clone() {
			return (Matrix2)super.clone();
		}
		public Matrix2 sum(MatrixBase m) {
			if(!(m instanceof Matrix2))
				throw new IllegalArgumentException("è possibile sommare ad una matrice 2x2 solo una matrice 2x2");
			Matrix2 aux = clone();
			aux.setElem(0,0, (getElem(0,0) + m.getElem(0,0)));
			aux.setElem(0,1, (getElem(0,1) + m.getElem(0,1)));
			aux.setElem(1,0, (getElem(1,0) + m.getElem(1,0)));
			aux.setElem(1,1, (getElem(1,1) + m.getElem(1,1)));
			return aux;
		}
		public Matrix2 dif(MatrixBase m) {
			if(!(m instanceof Matrix2))
				throw new IllegalArgumentException("è possibile sottrarre ad una matrice 2x2 solo una matrice 2x2");
			return this.sum(m.sProd(-1));
		}
		public Matrix2 sProd(double scalar) {
			Matrix2 aux = clone();
			aux.setElem(0,0, (getElem(0,0) * scalar));
			aux.setElem(0,1, (getElem(0,1) * scalar));
			aux.setElem(1,0, (getElem(1,0) * scalar));
			aux.setElem(1,1, (getElem(1,1) * scalar));
			return aux;
		}
		public Matrix2 trans() {
			Matrix2 aux = clone();
			aux.setElem(0,0, getElem(0,0));
			aux.setElem(1,1, getElem(1,1));
			aux.setElem(0,1, getElem(1,0));
			aux.setElem(1,0, getElem(0,1));
			return aux;
		}
		public Matrix2 prod(SquareMatrix m) {
			if(!(m instanceof Matrix2))
				throw new IllegalArgumentException("è possibile moltiplicare una matrice 2x2 solo con una matrice 2x2");
			return (Matrix2)super.prod(m);
		}
		public Matrix2 exp(int pot) {
			return (Matrix2)super.exp(pot);
		}
		public Matrix2 inv() {
			if(!isInvertible())
				throw new IllegalArgumentException("matrice non invertibile");
			Matrix2 aux = clone();
			aux.setElem(0,1, -getElem(0,1));
			aux.setElem(1,0, -getElem(1,0));
			aux.setElem(0,0, getElem(1,1));
			aux.setElem(1,1, getElem(0,0));
			return aux.sProd(1/det());
		}
		public Matrix2 adj() {
			Matrix2 aux = clone();
			aux.setElem(0,0, getElem(1,1));
			aux.setElem(1,1, getElem(0,0));
			aux.setElem(0,1, -getElem(0,1));
			aux.setElem(1,0, -getElem(1,0));
			return aux;
		}
		public double det() {
			return (getElem(0,0)*getElem(1,1) - getElem(0,1)*getElem(1,0));
		}
		public double trace() {
			return getElem(0,0)+getElem(1,1);
		}
		
	//Metodi ereditati:
		//	public int numRows();
		//	public int numCols();
		//	public boolean equals(Object obj);
		
		//	public double at(int i, int j);
		//	public void swapRows(int r1, int r2, int fromCol);
		//	public void swapCols(int c1, int c2, int fromRow);
		//	public void print(DataOutputStream os, String s);
		//	public void load(DataInputStream is);
		//	public int rank();
		//	public void fill(double val);
		//	public void setRandInt(int from, int to);
		//	public void setRandReal(double from, double to);
		
		//	public void setIdentity();
		//	public boolean isInvertible();
		
	//Eccezioni:
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..), swapRows(..), swapCols(..)
		//	NumberFormatException: load(..)
		//	IllegalArgumentException: load(..), setRandInt(..), setRandReal(..)
		//	RuntimeException: clone()
		
		//	ArithmeticException: exp(..)
		
		//	IllegalArgumentException: sum(..), dif(..), prod(..)
		//	ArithmeticException: inv()
	
} //fine Matrix2

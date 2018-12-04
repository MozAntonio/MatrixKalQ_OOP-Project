/* Matrix3.java */

package matrixkalq;
//import java.lang.IllegalArgumentException;


public class Matrix3 extends SquareMatrix {
	
	//Costruttori:
		public Matrix3(double init) { super(3,init); }
		public Matrix3() {super(3); }
		
	//Override:
		public Matrix3 clone() {
			return (Matrix3)super.clone();
		}
		public Matrix3 sum(MatrixBase m){
			if(!(m instanceof Matrix3))
				throw new IllegalArgumentException("è possibile sommare ad una matrice 3x3 solo una matrice 3x3");
			return (Matrix3)super.sum(m);
		}
		public Matrix3 dif(MatrixBase m) {
			if(!(m instanceof Matrix3))
				throw new IllegalArgumentException("è possibile sottrarre ad una matrice 3x3 solo una matrice 3x3");
			return (Matrix3)super.dif(m);
		}
		public Matrix3 sProd(double scalar) {
			return (Matrix3)super.sProd(scalar);
		}
		public Matrix3 trans() {
			return (Matrix3)super.trans();
		}
		public Matrix3 prod(SquareMatrix m) {
			if(!(m instanceof Matrix3))
				throw new IllegalArgumentException("è possibile moltiplicare una matrice 3x3 solo con una matrice 3x3");
			return (Matrix3)super.prod(m);
		}
		public Matrix3 exp(int pot) {
			return (Matrix3)super.exp(pot);
		}
		public Matrix3 inv() {
			return (Matrix3)super.inv();
		}
		public Matrix3 adj() {
			Matrix3 aux = clone();
			aux.setElem(0,0, (getElem(1,1)*getElem(2,2) - getElem(2,1)*getElem(1,2)));
			aux.setElem(1,1, (getElem(0,0)*getElem(2,2) - getElem(2,0)*getElem(0,2)));
			aux.setElem(2,2, (getElem(0,0)*getElem(1,1) - getElem(1,0)*getElem(0,1)));
			aux.setElem(1,0, (-((getElem(1,0)*getElem(2,2)) - (getElem(2,0)*getElem(1,2)))));
			aux.setElem(2,1, (-((getElem(0,0)*getElem(2,1)) - (getElem(2,0)*getElem(0,1)))));
			aux.setElem(0,1, (-((getElem(0,1)*getElem(2,2)) - (getElem(2,1)*getElem(0,2)))));
			aux.setElem(1,2, (-((getElem(0,0)*getElem(1,2)) - (getElem(1,0)*getElem(0,2)))));
			aux.setElem(2,0, (getElem(1,0)*getElem(2,1) - getElem(2,0)*getElem(1,1)));
			aux.setElem(0,2, (getElem(0,1)*getElem(1,2) - getElem(1,1)*getElem(0,2)));
			return aux;
		}
		public double det() {
			return ((getElem(0,0)*getElem(1,1)*getElem(2,2)+getElem(0,1)*getElem(1,2)*getElem(2,0)+getElem(0,2)*getElem(1,0)*getElem(2,1)) - (getElem(2,0)*getElem(1,1)*getElem(0,2)+getElem(2,1)*getElem(1,2)*getElem(0,0)+getElem(2,2)*getElem(1,0)*getElem(0,1)));
		}
		public double trace() {
			return getElem(0,0) + getElem(1,1) + getElem(2,2);
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
		
		//	ArithmeticException: inv(), exp(..)
		
		//	IllegalArgumentException: sum(..), dif(..), prod(..)
	
} //fine Matrix3

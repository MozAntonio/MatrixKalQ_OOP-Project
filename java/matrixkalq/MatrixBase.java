/* MatrixBase.java */

package matrixkalq;

//import java.lang.Cloneable;
//import java.lang.IllegalArgumentException;
import java.io.PrintStream;


//Abstract Base Class
public abstract class MatrixBase implements Cloneable {
	
	//Campi dati:
		private int rows;
		private int cols;
		
	//Costruttori
		public MatrixBase(int r, int c) {
			if(r<0 || c<0) {
				rows=0; cols=0;
				throw new IllegalArgumentException("creazione di una matrice con dimensioni negative non permessa");
			}
			rows=r; cols=c;
		}
		public MatrixBase() { this(0,0); }
		
	//Metodi virtuali puri:
		public abstract double getElem(int i, int j);
		public abstract void setElem(int i, int j, double val);
		public abstract void swapRows(int r1, int r2, int fromCol);
		public abstract void swapCols(int c1, int c2, int fromRow);
		public abstract void print(PrintStream ps, String separ);
		public abstract void load(String s);
		public abstract int rank();
		public abstract MatrixBase sum(MatrixBase m);
		public abstract MatrixBase dif(MatrixBase m);
		public abstract MatrixBase sProd(double scalar);
		public abstract MatrixBase trans();
		
	//Metodi propri:
		public int numRows() { return rows; }
		public int numCols() { return cols; }
		
		public MatrixBase clone() {
			MatrixBase aux = null;
			try {aux = (MatrixBase)super.clone(); }
			catch(CloneNotSupportedException e) { throw new RuntimeException("clone() ha fallito", e); }
			
			aux.rows = this.rows;
			aux.cols = this.cols;
			
			return aux;
		}
		
		public boolean equals(Object obj) {
			if(this == obj)
				return true;
			
			if(obj==null || getClass()!=obj.getClass())
				return false;
			
			MatrixBase other = (MatrixBase)obj;
			if(!(numRows()==other.numRows() && numCols()==other.numRows()))
				return false;
			
			for(int i=0; i<numRows(); ++i) //o: i<other.numRows()
				for(int j=0; j<numCols(); ++j) //o: j<other.numCols()
					if(getElem(i,j) != other.getElem(i,j))
						return false;
			
			return true;
		}
		
	//Eccezioni:
		//	IllegalArgumentException: MatrixBase(..)
		//	RuntimeException: clone()
	
} //fine MatrixBase

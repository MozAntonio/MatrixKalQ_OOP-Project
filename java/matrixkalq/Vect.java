/* Vect.java */

package matrixkalq;

//import java.lang.IllegalArgumentException;


public abstract class Vect extends RectMatrix {
	
	//Costruttori:
		public Vect(int n1, int n2, double init) {
			super(n1,n2,init);
			
			if(n1!=1 && n2!=1)
				throw new IllegalArgumentException("un vettore deve avere almeno una delle due dimensioni pari a '1'"); //dimensioni non valide
		}
		
		public Vect(int n1, int n2) {
			super(n1,n2);
			
			if(n1!=1 && n2!=1)
				throw new IllegalArgumentException("un vettore deve avere almeno una delle due dimensioni pari a '1'"); //dimensioni non valide
		}
		
		public Vect() { this(0,0); }
		
	//Metodi astratti:
		public abstract Vect sum(MatrixBase m);
		public abstract Vect dif(MatrixBase m);
		public abstract Vect sProd(double scalar);
		public abstract Vect rev();
		public abstract Vect trans();
		public abstract double getElem(int i); //overloading (in Java NON vige la regola della "name-hiding-rule")
		public abstract void setElem(int i, double val); //overloading (in Java NON vige la regola della "name-hiding-rule")
		
	//Override:
		public Vect clone() {
			return (Vect)super.clone();
		}
		
		public int rank() {
			int rank = 0;
			for(int i=0; (i<numElem()) && (rank==0); ++i)
				if(getElem(i) != 0)
					rank = 1;
			
			return rank;
		}
		
	//Metodi propri:
		public int numElem() {
			if(numCols() == 1) //è verticale
				return numRows();
			else //è orizzontale
				return numCols();
		}
		
		public void swapElem(int e1, int e2) {
			double temp = getElem(e1);
			setElem(e1, getElem(e2));
			setElem(e2, temp);
		}
		
	//Metodi ereditati:
		//	public int numRows();
		//	public int numCols();
		//	public boolean equals(Object obj);
		
		//	public String toString();
		//	public double getElem(int i, int j);
		//	public void setElem(int i, int j, double val);
		//	public void swapRows(int row1, int row2, int fromCol);
		//	public void swapCols(int col1, int col2, int fromRow);
		//	public void print(DataOutputStream os, String separator) throws IOException;
		//	public void load(DataInputStream is) throws EOFException, IOException;
		//	public void fill(double val);
		//	public void setRandInt(int from, int to);
		//	public void setRandReal(double from, double to);
		
	//Eccezioni:
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..), swapRows(..), swapCols(..)
		//	NumberFormatException: load(..)
		//	IllegalArgumentException: load(..), setRandInt(..), setRandReal(..)
		//	RuntimeException: clone()
		
		//	IllegalArgumentException: Vect(..)
		//	ArrayIndexOutOfBoundsException: swapElem(..) [a causa di getElem(int i) e/o setElem(int i, double val)]
		
} //fine Vect

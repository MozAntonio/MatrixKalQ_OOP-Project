/* VectHor.java */

package matrixkalq;

//import java.lang.IllegalArgumentException;

//Nota: A differenza del C++, in Java non è necessaria alcuna dichiarazione incompleta di classe per poterla utilizzare!


public class VectHor extends Vect {
	
	//Costruttori:
		public VectHor(int n, double init) { super(1,n,init); }
		public VectHor(int n) { super(1, n); }
		public VectHor() { this(0); }
		
	//Override:
		public VectHor clone() {
			return (VectHor)super.clone();
		}
		
	//Metodi 'concretizzati':
		public VectHor sum(MatrixBase m) {
			if(m instanceof VectHor) {
				
				if(numElem() != ((VectHor)m).numElem())
					throw new IllegalArgumentException("la somma è permessa solo tra vettori della stessa lunghezza"); //dimensioni non compatibili
				
				int e=numElem(); //o: e=((VectHor)m).numElem();
				VectHor aux = clone();
				
				for(int i=0; i<e; ++i)
					aux.setElem(i, (getElem(i) + ((VectHor)m).getElem(i)));
				
				return aux;
			}
			else { //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
				throw new IllegalArgumentException("è possibile sommare ad un vettore orizzontale solo un vettore orizzontale");
			}
		}
		
		public VectHor dif(MatrixBase m) {
			if(m instanceof VectHor) {
				return (this.sum(m.sProd(-1)));
			}
			else { //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
				throw new IllegalArgumentException("è possibile sottrarre ad un vettore orizzontale solo un vettore orizzontale");
			}
		}
		
		public VectHor sProd(double scalar) {
			VectHor aux = clone();
			
			for(int i=0; i<numElem(); ++i)
				aux.setElem(i, (getElem(i) * scalar));
			
			return aux;
		}
		
		public VectHor rev() {
			VectHor aux = clone();
			
			for(int i=0; i<numElem(); ++i)
				aux.setElem(i, getElem(numElem()-i-1));
			
			return aux;
		}
		
		//Un VectHor trasposto è un VectVert
		public VectVert trans() {
			VectVert aux = new VectVert(numElem());
			
			for(int i=0; i<numElem(); ++i)
				aux.setElem(i, getElem(i));
			
			return aux;
		}
		
		public double getElem(int i) {
			return getElem(0,i); //o: return super.getElem(0,i);
		}
		
		public void setElem(int i, double val) {
			setElem(0,i,val); //o: super.setElem(0,i,val);
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
		
		//	public int rank();
		//	public int numElem();
		//	public void swapElem(int e1, int e2);
		
	//Eccezioni:
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..), swapRows(..), swapCols(..)
		//	NumberFormatException: load(..)
		//	IllegalArgumentException: load(..), setRandInt(..), setRandReal(..)
		//	RuntimeException: clone()
		
		//	ArrayIndexOutOfBoundsException: swapElem(..) [a causa di getElem(int i) e/o setElem(int i, double val)]
		
		//	IllegalArgumentException: sum(..), dif(..)
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..)
		
} //fine VectHor

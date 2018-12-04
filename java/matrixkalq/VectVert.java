/* VectVert.java */

package matrixkalq;

//import java.lang.IllegalArgumentException;

//Nota: A differenza del C++, in Java non è necessaria alcuna dichiarazione incompleta di classe per poterla utilizzare!


public class VectVert extends Vect {
	
	//Costruttori:
		public VectVert(int n, double init) { super(n,1,init); }
		public VectVert(int n) { super(n, 1); }
		public VectVert() { this(0); }
		
	//Override:
		public VectVert clone() {
			return (VectVert)super.clone();
		}
		
	//Metodi 'concretizzati':
		public VectVert sum(MatrixBase m) {
			if(m instanceof VectVert) {
				
				if(numElem() != ((VectVert)m).numElem())
					throw new IllegalArgumentException("la somma è permessa solo tra vettori della stessa lunghezza"); //dimensioni non compatibili
				
				int e=numElem(); //o: e=((VectVert)m).numElem();
				VectVert aux = clone();
				
				for(int i=0; i<e; ++i)
					aux.setElem(i, (getElem(i) + ((VectVert)m).getElem(i)));
				
				return aux;
			}
			else { //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
				throw new IllegalArgumentException("è possibile sommare ad un vettore verticale solo un vettore verticale");
			}
		}
		
		public VectVert dif(MatrixBase m) {
			if(m instanceof VectVert) {
				return (this.sum(m.sProd(-1)));
			}
			else { //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
				throw new IllegalArgumentException("è possibile sottrarre ad un vettore verticale solo un vettore verticale");
			}
		}
		
		public VectVert sProd(double scalar) {
			VectVert aux = clone();
			
			for(int i=0; i<numElem(); ++i)
				aux.setElem(i, (getElem(i) * scalar));
			
			return aux;
		}
		
		public VectVert rev() {
			VectVert aux = clone();
			
			for(int i=0; i<numElem(); ++i)
				aux.setElem(i, getElem(numElem()-i-1));
			
			return aux;
		}
		
		//Un VectVert trasposto è un VectHor
		public VectHor trans() {
			VectHor aux = new VectHor(numElem());
			
			for(int i=0; i<numElem(); ++i)
				aux.setElem(i, getElem(i));
			
			return aux;
		}
		
		public double getElem(int i) {
			return getElem(i,0); //o: return super.getElem(i,0);
		}
		
		public void setElem(int i, double val) {
			setElem(i,0,val); //o: super.setElem(i,0,val);
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
		
} //fine VectVert

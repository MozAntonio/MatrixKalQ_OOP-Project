/* RectMatrix.java */

package matrixkalq;

//import java.lang.IllegalArgumentException;


public class RectMatrix extends DenseMatrix {
	
	//Costruttori:
		public RectMatrix(int r, int c, double init) {
			super(r,c,init);
			
			if((r==c) && (r!=0)) //o: ... && (c!=0)
				throw new IllegalArgumentException("una matrice rettangolare deve avere un numero diverso di righe e colonne"); //dimensioni non valide
		}
		
		public RectMatrix(int r, int c) {
			super(r,c);
			
			if((r==c) && (r!=0)) //o: ... && (c!=0)
				throw new IllegalArgumentException("una matrice rettangolare deve avere un numero diverso di righe e colonne"); //dimensioni non valide
		}
		
		public RectMatrix() { this(0,0); }
		
	//Override:
		public RectMatrix clone() {
			return (RectMatrix)super.clone();
		}
		
	//Metodi 'concretizzati':
		public RectMatrix sum(MatrixBase m) {
			if(m instanceof RectMatrix) {
				
				if(!(numRows()==m.numRows() && numCols()==m.numCols()))
					throw new IllegalArgumentException("la somma è permessa solo tra matrici rettangolari delle stesse dimensioni"); //dimensioni non compatibili
				
				int r=numRows(), c=numCols(); //o: r=m.numRows(), c=m.numCols();
				RectMatrix aux = clone();
				
				for(int i=0; i<r; ++i)
					for(int j=0; j<c; ++j)
						aux.setElem(i, j, (getElem(i,j) + m.getElem(i,j)));
				
				return aux;
			}
			else { //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
				throw new IllegalArgumentException("è possibile sommare ad una matrice rettangolare solo una matrice rettangolare");
			}
		}
		
		public RectMatrix dif(MatrixBase m) {
			if(m instanceof RectMatrix) {
				return (this.sum(m.sProd(-1)));
			}
			else { //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
				throw new IllegalArgumentException("è possibile sottrarre ad una matrice rettangolare solo una matrice rettangolare");
			}
		}
		
		public RectMatrix sProd(double scalar) {
			int r=numRows(), c=numCols();
			RectMatrix aux = clone();
			
			for(int i=0; i<r; ++i)
				for(int j=0; j<c; ++j)
					aux.setElem(i, j, (getElem(i,j) * scalar));
			
			return aux;
		}
		
		public RectMatrix trans() {
			int r=numRows(), c=numCols();
			RectMatrix aux = new RectMatrix(c,r);
			
			for(int i=0; i<r; ++i)
				for(int j=0; j<c; ++j)
					aux.setElem(j, i, getElem(i,j));
			
			return aux;
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
		//	public int rank();
		//	public void fill(double val);
		//	public void setRandInt(int from, int to);
		//	public void setRandReal(double from, double to);
		
	//Eccezioni:
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..), swapRows(..), swapCols(..)
		//	NumberFormatException: load(..)
		//	IllegalArgumentException: load(..), setRandInt(..), setRandReal(..)
		//	RuntimeException: clone()
		
		//	IllegalArgumentException: RectMatrix(..), sum(..), dif(..)
		
} //fine RectMatrix

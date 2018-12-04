/* DenseMatrix.java */

package matrixkalq;

//import java.lang.Math;
//import java.lang.IllegalArgumentException;
//import java.lang.NumberFormatException;
import java.util.Vector;
import java.util.concurrent.ThreadLocalRandom;
import java.io.PrintStream;


//Abstract Base Class
public abstract class DenseMatrix extends MatrixBase {
	
	//Campi dati:
		private Vector<Vector<Double>> m;
		
	//Costruttori:
		public DenseMatrix(int r, int c, double init) {
			super(r,c);
			m = new Vector<Vector<Double>>(r);
			m.setSize(r);
			
			for(int i=0; i<r; ++i) {
				m.set(i, new Vector<Double>(c));
				m.get(i).setSize(c);
				for(int j=0; j<c; ++j)
					m.get(i).set(j,init);
			}
		}
		
		public DenseMatrix(int r, int c) {
			super(r,c);
			m = new Vector<Vector<Double>>(r);
			m.setSize(r);
			
			for(int i=0; i<r; ++i) {
				m.set(i, new Vector<Double>(c));
				m.get(i).setSize(c);
			}
		}
		
		public DenseMatrix() { this(0,0); }
		
	//Metodi astratti:
		public abstract DenseMatrix sum(MatrixBase m);
		public abstract DenseMatrix dif(MatrixBase m);
		public abstract DenseMatrix sProd(double s);
		public abstract DenseMatrix trans();
		
	//Override:
		public DenseMatrix clone() {
		
			DenseMatrix aux = (DenseMatrix)super.clone();
			
			int r=numRows(), c=numCols();
			Vector<Vector<Double>> m_aux = new Vector<Vector<Double>>(r);
			m_aux.setSize(r);
			for(int i=0; i<r; ++i) {
				m_aux.set(i, new Vector<Double>(c));
				m_aux.get(i).setSize(c);
				for(int j=0; j<c; ++j)
					m_aux.get(i).set(j, this.m.get(i).get(j));
			}
			aux.m = m_aux;
			
			return aux;
		}
		
		public String toString() {
			String aux = "";
			for(int i=0; i<numRows(); ++i) {
				for(int j=0; j<numCols(); ++j) {
						if(m.get(i).get(j) == null)
							aux = aux + "null" + "\t";
						else
							aux = aux + getElem(i,j) + "\t";
				}
				aux = aux + "\n";
			}
			return aux;
		}
		
	//Metodi 'concretizzati':
		public double getElem(int i, int j) { return m.get(i).get(j); }
		
		public void setElem(int i, int j, double val) { m.get(i).set(j,val); }
		
		public void swapRows(int row1, int row2, int fromCol) {
			for(int j=fromCol; j<numCols(); ++j) {
				double temp = getElem(row1,j);
				setElem(row1,j, getElem(row2,j));
				setElem(row2,j, temp);
			}
		}
		
		public void swapCols(int col1, int col2, int fromRow) {
			for(int i=fromRow; i<numRows(); ++i) {
				double temp = getElem(i,col1);
				setElem(i,col1, getElem(i,col2));
				setElem(i,col2, temp);
			}
		}
		
		public void print(PrintStream ps, String separ) {
			String aux = "";
			for(int i=0; i<numRows(); ++i) {
				for(int j=0; j<numCols(); ++j) {
						if(m.get(i).get(j) == null)
							aux = aux + "null" + separ;
						else
							aux = aux + getElem(i,j) + separ;
				}
				aux = aux + "\n";
			}
			ps.println(aux);
		}
		
		public void load(String s) {
			//controlla che sullo stream di input:
			// ci siano almeno i caratteri necessari per riempire la matrice
			//	valori aggiuntivi (validi o meno) verranno ignorati
			// che tutti i caratteri necessari siano validi (double)
			//altrimenti:
			// eccezione e il contenuto della matrice è inconsistente (garbage)
			
			if(s == null || s.isEmpty())
				s=" ";
			
			String[] temp = (s.replaceAll("\\s+"," ")).split(" ");
			
			if(temp.length < numRows()*numCols())
				throw new IllegalArgumentException("valori non sufficienti");
			else //ne ho abbastanza, verifico siano double e li carico
				for(int i=0; i<numRows(); ++i)
					for(int j=0; j<numCols(); ++j) {
						try { setElem(i,j, Double.parseDouble(temp[i*numCols()+j])); }
						catch(NumberFormatException e) { throw new NumberFormatException("valori di tipo errato"); }
					}
		}
		
		//Calcola il rango tramite il metodo di eliminazione di Gauss con pivoting parziale
		public int rank() {
			int rig=numRows(), col=numCols(), rk=0;
			DenseMatrix aux = clone(); //matrice ausiliaria d'appoggio
			boolean finito = false;
			
			for(int d=0; d<col && d<rig && !finito; ++d) {
				
				//cerco il massimo pivot sotto di me
				int pivot_row = d;
				double cur = Math.abs(aux.getElem(d,d));
				for(int k=d+1; k<rig; ++k)
					if(Math.abs(aux.getElem(k,d)) > cur) {
						pivot_row = k;
						cur = aux.getElem(k,d);
					}
				
				//se ne ho trovato uno maggiore, scambio la riga attuale con quella con il pivot massimo
				if(pivot_row != d)
					aux.swapRows(d, pivot_row, d); //solo gli elem da 'd' in poi, gli altri sono zeri
				
				if(Math.abs(aux.getElem(d,d)) < 0.00000000000001) { //questa colonna ha solo zeri da qua in giù
					if(d+1<col) { //ho ancora colonne da controllare
						aux.swapCols(d, col-1, d); //col-1 è l'ultima, solo gli elem da 'd' in giù, gli altri non servono
						col--; //la colonna che sposto è inutile, quindi la escludo
						d--; //rifaccio questo giro d'iteraz, lo swap ha messo un nuovo elem in A[d][d]
					}
					else { //ho finito le colonne, quindi ho finito
						finito=true; //rk a questo punto sarà il num di col linear indip, cioè il rango
					}
				}
				else { //aux.getElem(d,d)!=0
					//devo azzerare gli elem sotto di me, cioè:
					//aux.getElem(d+1,d), aux.getElem(d+2,d), ..., aux.getElem(i,d) con: d<i<rig
					for(int i=d+1; i<rig; ++i) {
						if(aux.getElem(i,d) != 0) { //va annullato
							//per annullarlo:
							//sostituisco l'intera riga in cui risiede l'elem da annullare (la i-esima)
							//con la differenza tra essa (la i-esima) e quella del 'pivot' (la d-esima)
							//moltiplicata per un coefficiente (coef)
							//coef è il rapporto tra l'elem da annullare (aux.getElem(i,d)) e il pivot (aux.getElem(d,d))
							double coef = aux.getElem(i,d) / aux.getElem(d,d);
							for(int j=d; j<col; ++j)
								aux.setElem(i, j, (aux.getElem(i,j) - (aux.getElem(d,j)*coef)));
						}
						//else //l'elem è già zero, passo al prossimo
					}
					rk++; //questa, in cui A[d][d]!=0, è una colonna 'utile' che contribuisce al rango
				}
			}
			return rk;
		}
		
	//Metodi propri:
		public void fill(double val) {
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					setElem(i,j,val);
		}
		
		public void setRandInt(int from, int to) { //rand in [from,to)
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					setElem(i, j, ThreadLocalRandom.current().nextInt(from, to));
		}
		
		public void setRandReal(double from, double to) { //rand in from[from,to)
			for(int i=0; i<numRows(); ++i)
				for(int j=0; j<numCols(); ++j)
					setElem(i, j, ThreadLocalRandom.current().nextDouble(from, to));
		}
		
	//Metodi ereditati:
		//	public int numRows();
		//	public int numCols();
		//	public boolean equals(Object obj);
		
	//Eccezioni:
		//	ArrayIndexOutOfBoundsException: getElem(..), setElem(..), swapRows(..), swapCols(..)
		//	NumberFormatException: load(..)
		//	IllegalArgumentException: load(..), setRandInt(..), setRandReal(..)
		//	RuntimeException: clone()
		
} //fine DenseMatrix

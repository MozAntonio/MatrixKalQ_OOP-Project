import matrixkalq.*;

public class Use {
	public static void main(String args[]) {
		try {
			MatrixBase mb1;
			MatrixBase mb2;

			//Esempi: Matrice 2x2
			System.out.println("Esempi su matrici 2x2:");
			System.out.println();

			//Matrice inizializzata con tutti gli elementi == 2.5:
			mb1 = new Matrix2(2.5);

			//Matrice inizializzata grazie al metodo "load":
			mb2 = new Matrix2();
			mb2.load("2 0 -1 3.1");

			//Stampa delle matrici iniziali:
			System.out.println("Prima matrice:");
			System.out.println(mb1);
			System.out.println();
			System.out.println("Seconda matrice:");
			mb2.print(System.out,"\t");
			System.out.println();

			//Rango:
			System.out.println("Rango corretto (matrice 1): 1");
			System.out.println("Rango effettivo (matrice 1): " + mb1.rank());
			System.out.println();

			//Determinante:
			System.out.println("Determinante corretto (matrice 2): 6.2");
			System.out.println("Determinante effettivo (matrice 2): " + ((Matrix2)mb2).det());
			System.out.println();

			//Traccia:
			System.out.println("Traccia corretta (matrice 2): 5.1");
			System.out.println("Traccia effettiva (matrice 2): " + ((Matrix2)mb2).trace());
			System.out.println();

			//Se è invertibile -> Inversa:
			System.out.println("Se la matrice 1 è invertibile, allora calcolo l'inversa:");
			if(((Matrix2)mb1).isInvertible()) {
				System.out.println();
				System.out.println("Inversa (matrice 1): " + ((Matrix2)mb1).inv());
				System.out.println();
			}
			else {
				System.out.println("Matrice 1 non invertibile.");
				System.out.println();
			}

			//Se è invertibile -> Inversa:
			System.out.println("Se la matrice 2 è invertibile, allora calcolo l'inversa:");
			if(((Matrix2)mb2).isInvertible()) {
				System.out.println();
				System.out.println("Inversa (matrice 2): " + ((Matrix2)mb2).inv());
				System.out.println();
			}
			else {
				System.out.println("Matrice 2 non invertibile.");
				System.out.println();
			}

			//Somma:
			System.out.println("Somma di matrice 1 + matrice 2:");
			System.out.println(mb1.sum(mb2));
			System.out.println();

			System.out.println();
			System.out.println();


			//Esempi: Matrice 3x3
			System.out.println("Esempi su matrici 3x3:");
			System.out.println();

			//Matrice inizializzata con tutti gli elementi == 2:
			mb1 = new Matrix3();
			((Matrix3)mb1).fill(2);

			//Matrice inizializzata grazie al metodo "load":
			mb2 = new Matrix3();
			mb2.load("0.15 -2.5 5 1 1 3 5.5 -1 2");

			//Stampa delle matrici iniziali:
			System.out.println("Prima matrice:");
			System.out.println(mb1);
			System.out.println();
			System.out.println("Seconda matrice:");
			mb2.print(System.out,"\t");
			System.out.println();

			//Determinante:
			System.out.println("Determinante corretto (matrice 2): -68");
			System.out.println("Determinante effettivo (matrice 2): " + ((Matrix3)mb2).det());
			System.out.println();

			//Aggiunta:
			System.out.println("Aggiunta (matrice 2):");
			System.out.println(((Matrix3)mb2).adj());
			System.out.println();

			//Trasposta:
			System.out.println("Trasposta (matrice 2):");
			System.out.println(mb2.trans());
			System.out.println();

			//Prodotto per scalare:
			System.out.println("Prodotto per lo scalare '0.5' (matrice 1):");
			System.out.println(mb1.sProd(0.5));
			System.out.println();

			//Esponenziale:
			System.out.println("Esponenziale alla '0' (matrice 1):");
			System.out.println(((Matrix3)mb1).exp(0));
			System.out.println();

			//Prodotto:
			System.out.println("Prodotto di matrice 1 * matrice 2:");
			System.out.println(((Matrix3)mb1).prod((Matrix3)mb2));
			System.out.println();

			System.out.println();
			System.out.println();


			//Esempi: Matrice NxN (con N=5)
			System.out.println("Esempi su matrici NxN (con N=5):");
			System.out.println();

			//Matrice inizializzata grazie al metodo "load":
			mb1 = new SquareMatrix(5);
			mb1.load("1 0 2 4 7 9 -2 0.3 -4.1 0 0 1 7 5 2 10 -12 20.5 3 1 24 3.5 3.25 -2.14 7");

			//Matrice inizializzata con tutti gli elementi == -1 e poi modificati alcuni elementi con "setElem(..)":
			mb2 = new SquareMatrix(5, -1);
			mb2.setElem(0,2,0);
			mb2.setElem(1,4,-6);
			mb2.setElem(1,3,14.5);
			mb2.setElem(3,0,21);
			mb2.setElem(3,2,4);
			mb2.setElem(2,1,0.36);
			mb2.setElem(3,4,2);
			mb2.setElem(0,0,8.2);

			//Stampa delle matrici iniziali:
			System.out.println("Prima matrice:");
			System.out.println(mb1);
			System.out.println();
			System.out.println("Seconda matrice:");
			mb2.print(System.out,"\t");
			System.out.println();

			//Determinante:
			System.out.println("Determinante corretto (matrice 1): 4996.895");
			System.out.println("Determinante effettivo (matrice 1): " + ((SquareMatrix)mb1).det());
			System.out.println();

			//Traccia:
			System.out.println("Traccia corretta (matrice 1): 16");
			System.out.println("Traccia effettiva (matrice 1): " + ((SquareMatrix)mb1).trace());
			System.out.println();

			//Aggiunta:
			System.out.println("Aggiunta (matrice 2):");
			System.out.println(((SquareMatrix)mb2).adj());
			System.out.println();

			//Esponenziale:
			System.out.println("Esponenziale alla '2' (matrice 1):");
			System.out.println(((SquareMatrix)mb1).exp(0));
			System.out.println();

			//Se è invertibile -> Inversa:
			System.out.println("Se la matrice 2 è invertibile, allora calcolo l'inversa:");
			if(((SquareMatrix)mb2).isInvertible()) {
				System.out.println();
				System.out.println("Inversa (matrice 2): " + ((SquareMatrix)mb2).inv());
				System.out.println();
			}
			else {
				System.out.println("Matrice 2 non invertibile.");
				System.out.println();
			}

			//Differenza:
			System.out.println("Differenza di matrice 2 - matrice 1:");
			System.out.println(mb2.dif(mb1));
			System.out.println();

			//Somma:
			((SquareMatrix)mb2).setRandReal(-25.3, 50.64);
			System.out.println("Somma di matrice 1 + matrice di numeri reali casuali nell'intervallo [-25.3, +50.64):");
			System.out.println(mb1.sum(mb2));
			System.out.println();

			//Matrice 2 convertita in matrice identità:
			((SquareMatrix)mb2).setIdentity();
			System.out.println("Matrice identità 5x5:");
			System.out.println(mb2);
			System.out.println();

			System.out.println();
			System.out.println();


			//Esempi: Matrice NxM (con N=2 e M=5)
			System.out.println("Esempi su matrici NxM (con N=2 e M=5):");
			System.out.println();

			//Matrice inizializzata grazie al metodo "load":
			mb1 = new RectMatrix(2, 5);
			mb1.load("1 0 4 7 89 -5 0.2 4 1.26 3");

			//Matrice inizializzata con tutti gli elementi == 0 e poi modificati alcuni elementi con "setElem(..)":
			mb2 = new RectMatrix(2, 5, 0);
			mb2.setElem(0,2,3);
			mb2.setElem(1,0,-0.4);
			mb2.setElem(1,4,20.37);
			mb2.setElem(1,1,9);

			//Stampa delle matrici iniziali:
			System.out.println("Prima matrice:");
			System.out.println(mb1);
			System.out.println();
			System.out.println("Seconda matrice:");
			mb2.print(System.out,"\t");
			System.out.println();

			//Rango:
			System.out.println("Rango corretto (matrice 1): 2");
			System.out.println("Rango effettivo (matrice 1): " + mb1.rank());
			System.out.println();

			//Trasposta:
			System.out.println("Trasposta (matrice 2):");
			System.out.println(mb2.trans());
			System.out.println();

			//Differenza:
			System.out.println("Differenza di matrice 1 - matrice 2:");
			System.out.println(mb1.dif(mb2));
			System.out.println();

			System.out.println();
			System.out.println();


			//Esempi: Vettore 1xN (con N=8)
			System.out.println("Esempi su vettori 1xN (con N=8):");
			System.out.println();
			System.out.println();

			//Vettore inizializzato grazie al metodo "load":
			mb1 = new VectHor(8);
			mb1.load("1 2 3 4 5 6 7 8");

			//Vettore inizializzato grazie al metodo "load":
			mb2 = new VectHor(8);
			mb2.load("6 0 1 7 0 0 -2.8 3.6");

			//Stampa delle matrici iniziali:
			System.out.println("Primo vettore:");
			System.out.println(mb1);
			System.out.println();
			System.out.println("Secondo vettore:");
			mb2.print(System.out,"\t");
			System.out.println();

			//Rango:
			System.out.println("Rango corretto (vettore 2): 1");
			System.out.println("Rango effettivo (vettore 2): " + mb2.rank());
			System.out.println();

			//Inverso:
			System.out.println("Vettore in ordine inverso (vettore 1):");
			System.out.println(((VectHor)mb1).rev());
			System.out.println();

			//Trasposto:
			System.out.println("Trasposto (vettore 2):");
			System.out.println(mb2.trans());
			System.out.println();

			System.out.println();
			System.out.println();


			//Esempi: Vettore Nx1 (con N=4)
			System.out.println("Esempi su vettori Nx1 (con N=4):");
			System.out.println();

			//Vettore inizializzato grazie al metodo "load":
			mb1 = new VectVert(4);
			mb1.load("0 1 -2 6");

			//Vettore inizializzato con tutti gli elementi == 10.43:
			mb2 = new VectVert(4);
			((VectVert)mb2).fill(10.43);

			//Stampa delle matrici iniziali:
			System.out.println("Primo vettore:");
			System.out.println(mb1);
			System.out.println();
			System.out.println("Secondo vettore:");
			mb2.print(System.out,"\t");
			System.out.println();

			//Inverso:
			System.out.println("Vettore in ordine inverso (vettore 1):");
			System.out.println(((VectVert)mb1).rev());
			System.out.println();

			//Somma:
			System.out.println("Somma di vettore 2 + vettore 1:");
			System.out.println(mb2.sum(mb1));
			System.out.println();
		}
		catch(IllegalArgumentException e) {
			System.out.println("Eccezione 'IllegalArgumentException': " + e.getMessage());
		}

		System.out.println();
		System.out.println();
		System.out.println();


		//Tentativi di operazioni non lecite, che sollevano eccezioni:

		//Somma tra matrici quadrate con diverse dimensioni:
		MatrixBase mb1 = new Matrix2(2);
		MatrixBase mb2 = new SquareMatrix(6, -3.2);

		try {
			System.out.println("Somma tra matrice 2x2 e matrice quadrata 6x6:");
			System.out.println(mb1.sum(mb2));
		}
		catch (IllegalArgumentException e) {
			System.out.println("Eccezione esempio 1: " + e.getMessage());
			System.out.println();
		}

		//Differenza tra una matrice rettangolare ed un vettore verticale:
		mb1 = new RectMatrix(3,4,8);
		mb2 = new VectVert(13,2.3);

		try {
			System.out.println("Differnza tra matrice rettangolare 3x4 e vettore verticale 13x1:");
			System.out.println(mb1.dif(mb2));
		}
		catch (IllegalArgumentException e) {
			System.out.println("Eccezione esempio 2: " + e.getMessage());
			System.out.println();
		}

		System.out.println();
		System.out.println();
		System.out.println();
		System.out.println();

		System.out.println("### END JAVA EXAMPLES ###");
		
	} //fine main()
}
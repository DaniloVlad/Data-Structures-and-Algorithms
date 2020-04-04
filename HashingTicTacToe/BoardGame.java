import java.lang.Math.*;
public class BoardGame {
	//initialization variables for BoardGame
	private char[][] gameBoard;
	private int boardSize;
	private int emptyPositions;
	private int maxLevels;
	
	
	public BoardGame(int board_size, int empty_positions, int max_levels) {
		//assign to instance variables
		boardSize = board_size;
		emptyPositions = empty_positions;
		maxLevels = max_levels;
		gameBoard = new char[boardSize][boardSize];
		//initial boardGame with all 'empty' tiles
		for (int row = 0; row < boardSize; row ++)
		    for (int col = 0; col < boardSize; col++)
		        gameBoard[row][col] = 'g';
	}
	
	//return new HashDict object
	public HashDictionary makeDictionary() {
		return new HashDictionary();
	}
	
	//convert board to string from top to bottom then left to right
	private String stringifyBoard() {
		String s = "";
		for (int col = 0; col < boardSize; col ++)
			for(int row = 0; row < boardSize; row++)
		        s += gameBoard[row][col];
		return s;
	}
	
	//check if config is repeated
	public int isRepeatedConfig(HashDictionary dict) {
		String s = stringifyBoard();
		return dict.getScore(s);
	}
	
	//put config into HashDict
	public void putConfig(HashDictionary dict, int score) {
		String s = stringifyBoard();
		Configuration data = new Configuration(s, score); 
		//catch config already in HashDict error
		try {
			dict.put(data);
		} catch(DictionaryException e) {
			//handle exception by notifying user
			System.out.println(e);
		}
		
	}
	
	//helper function for updating board
	public void savePlay(int row, int col, char symbol) {
		gameBoard[row][col] = symbol;
	}
	
	//helper function to see if position is empty
	public boolean positionIsEmpty(int row, int col) {
		return (gameBoard[row][col] == 'g');
	}
	
	//helper function to see if gb[r][c] is a comp tile
	public boolean tileOfComputer(int row, int col) {
		return (gameBoard[row][col] == 'o');
	}
	
	//helper function to see if gb[r][c] is a player tile
	public boolean tileOfHuman(int row, int col) {
		return (gameBoard[row][col] == 'b');
	}
	
	//function to decide winner
	public boolean wins(char symbol) {
		//construct winSeq as string of length boardSize and symbol repeating
		//n=3, symbol='o', winSeq = "ooo"
		String winSeq = "";
		for(int k=0; k<boardSize; k++) winSeq += symbol;
		//loop through 2D array and convert rows into String sequence
		for (int row = 0; row < boardSize; row ++) {
			String test = new String(gameBoard[row]);
			//compare the rows sequence to winSeq. row is "bog" will not return 0
			//but row "ooo" will return 0, and true
			if(test.compareTo(winSeq) == 0) return true;
			test = "";
			//construct test String for column sequence
			for(int col = 0; col < boardSize; col ++) {
				test += gameBoard[col][row];
			}
			//same logic as above
			if(test.compareTo(winSeq) == 0) return true;
		}
		//here we check the diagnos, since the board is nxn we have 2 diagnols
		//d1 = {(0,0),(1,1)....(n,n)} and d2 = {(0,n), (1, n-1) .... (n, 0)}
		String d1 = "", d2 = "";
		for(int k = 0; k < boardSize; k++) {
			d1 += gameBoard[k][k];
			d2 += gameBoard[k][boardSize-1-k];
		}
		//if either diagnol contains the winSeq return true
		if(d2.compareTo(winSeq) == 0 || d1.compareTo(winSeq) == 0) return true;
		//catch all false, there was no winner.
		return false;
		
		   
	}
	
	public boolean isDraw(char symbol, int empty_positions) {
		
		boolean didWin = wins('o') || wins('b');
		//if theres a winner return.
		if(didWin) return false;
		//no explicit winner
		else {
			//count empty slots
			int count = 0;
			for(int r = 0; r < boardSize; r ++)
				for(int c = 0; c < boardSize; c++)
					if(gameBoard[r][c] == 'g') count +=1;
			//no winner && no empty positions
			if(empty_positions == count) return true; 
			//the adjacent check  && no winner
			else if(empty_positions > 0 && empty_positions == count) {
				//loop through the whole board
				for(int row = 0; row < boardSize; row++) {
					for(int col = 0; col < boardSize; col++) {
						//found 1 of the count empty_positions
						if(gameBoard[row][col] == 'g') {
							//this is made to avoid accessing the array out of bounds
							//corners have 2 adjacent elements, tiles in the outter most rows/cols 
							//have 3 adjacent elemts, everything has 4.
							int adjR = (row == 0 || row == boardSize-1 ? 1:2);
							int adjC = (col == 0 || col == boardSize-1 ? 1:2);
							int adj = adjR+adjC;
							if(adj == 2) { // corner elements
								if(row == 0) { 
									if(col == 0) { //row 0, col 0
										if(gameBoard[row][col+1] == symbol || gameBoard[row+1][col] == symbol) 
											return false;
									}
									else { //row 0, col n-1
										if(gameBoard[row][col-1] == symbol || gameBoard[row+1][col] == symbol)
											return false;
									}
								}
								else { //row n-1
									if(col == 0) { //col 0
										if(gameBoard[row][col+1] == symbol || gameBoard[row-1][col] == symbol)
											return false;
									}
										
									else { //col n-1
										if(gameBoard[row][col-1] == symbol || gameBoard[row-1][col] == symbol)
											return false;
									}
								}
							}
							else if(adj == 3) {
								if(adjR == 2) {  //2 rows adjacent
									if(col == 0) { //has row above and below and 1 column beside
										if(gameBoard[row+1][col] == symbol || gameBoard[row-1][col] ==symbol
												|| gameBoard[row][col+1] == symbol) return false;
									}
									else { //2 rows and 1 column before
										if(gameBoard[row+1][col] == symbol || gameBoard[row-1][col] ==symbol
												|| gameBoard[row][col-1] == symbol) return false;
									}		
								}
								else { //2 adjacent columns
									if(row == 0) {  //1 adjacent row below current
										if(gameBoard[row+1][col] == symbol || gameBoard[row][col+1] ==symbol
												|| gameBoard[row][col-1] == symbol) return false;
									}
										
									else { //1 adjacent row above current
										if(gameBoard[row-1][col] == symbol || gameBoard[row][col+1] ==symbol
												|| gameBoard[row][col-1] == symbol) return false;
									}
										
								}
							}
							else { //central piece has 4 adjacent objects
								if(gameBoard[row+1][col] == symbol || gameBoard[row-1][col] == symbol ||
										gameBoard[row][col+1] == symbol && gameBoard[row][col-1] == symbol)
											return false;
							}
						}
					}
				}
				
				//if loop finishes and nothing is returned
				//but all positions are filled than it is a draw
				return true;
			}
			
		} 
		//catch all
		return false;
	}
	
	public int evalBoard(char symbol, int empty_positions) {
		//using above functions to evaluate the board
		if(wins('o')) return 3;
		else if(wins('b')) return 0;
		else if(isDraw(symbol, empty_positions)) return 2;
		else return 1;
	}
}

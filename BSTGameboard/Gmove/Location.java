
public class Location {
	private int x, y;
	
	public Location(int x, int y) {
		this.x = x;
		this.y = y;
		
	}
	
	public int xCoord() {
		return this.x;
	}
	
	public int yCoord() {
		return this.y;
	}
	
	public int compareTo(Location p) {
		if((this.x < p.xCoord()) | (this.x == p.xCoord() && this.y < p.yCoord()))
			return -1;
		if(this.y == p.yCoord()) {
			return 0;
		}
		return 1;
	}
}

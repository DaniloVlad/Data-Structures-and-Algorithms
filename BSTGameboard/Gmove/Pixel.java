
public class Pixel {
		private Location p;
		private int color;
		//2 gets and a constructor
		public Pixel(Location p, int color) {
			this.p = p;
			this.color = color;
		}
		
		public Location getLocation() {
			return this.p;
		}
		
		public int getColor() {
			return this.color;
		}
}

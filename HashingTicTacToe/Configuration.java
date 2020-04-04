
public class Configuration {
	//instance variables
	private String config;
	private int score;
	
	public Configuration(String config, int score) {
		//assign main vars
		this.config = config;
		this.score = score;
	}
	
	//getters for instance variables
	public String getStringConfiguration() {
		return config;
	}
	
	public int getScore() {
		return score;
	}
}

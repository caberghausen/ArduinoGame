
import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	

	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = false; // Default is to NOT be in debug mode
	}
		
	// TODO: Add writeByte() method from Studio 5 
	public void writeByte(byte data) {
		String hex = Integer.toHexString((int)data);
		if(debug) {
			try {
				port.writeByte(data);
			} catch (SerialPortException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("[0x"+hex+"]");
		}
		else {
			try {
				port.writeByte(data);
			} catch (SerialPortException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return;
	}
	
	
	// TODO: Add available() method
	public boolean available() throws SerialPortException {
		boolean answer = port.getInputBufferBytesCount()>0 ? true : false;
		return answer;
	}
	
	// TODO: Add readByte() method	
	public byte readByte() throws SerialPortException {
		byte[] data = port.readBytes(1);
		String hex = Integer.toHexString((int)data[0]);
		if(this.debug) {
			System.out.print("[0x"+hex+"] ");
		}
		return data[0];
		
	}
	
	// TODO: Add a main() method
	public static void main(String[] args) throws SerialPortException {
		SerialComm port1 = new SerialComm("/dev/cu.usbserial-DN03FR6B");
		port1.debug = true;
		while(true) {
			if(port1.available()) {
				port1.readByte();
			}
		}
	}
}

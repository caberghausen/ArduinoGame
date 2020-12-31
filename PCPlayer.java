import java.awt.event.KeyEvent;

import jssc.SerialPortException;


public class PCPlayer
{
	final private SerialComm port;
	private byte temp;
	public PCPlayer(String portname) throws SerialPortException {
		port = new SerialComm(portname);
	}
	
	


	public void move() throws InterruptedException
	{
		if(StdDraw.isKeyPressed(KeyEvent.VK_UP))
		{
			temp = 1;
			port.writeByte((byte)temp);
			Thread.sleep(725);
		}
		

		else if(StdDraw.isKeyPressed(KeyEvent.VK_DOWN))
		{
			temp = 2;
			port.writeByte((byte)temp);
			Thread.sleep(725);
		}

		else if(StdDraw.isKeyPressed(KeyEvent.VK_LEFT))
		{
			temp = 3;
			port.writeByte((byte)temp);
			Thread.sleep(725);
		}

		else if(StdDraw.isKeyPressed(KeyEvent.VK_RIGHT))
		{
			temp = 4;
			port.writeByte((byte)temp);
			Thread.sleep(725);
		}


	}
	public static void main(String[] args) throws SerialPortException, InterruptedException {
		PCPlayer p = new PCPlayer("/dev/cu.usbserial-DN03FR6B");
		
		while(true) {
			p.move();
		}
	}


}
package kawigi.util;
import java.io.*;
import javax.swing.text.*;

/**
 *	I couldn't do local compiling and testing without this.
 *	
 *	This contains and manages a process and forwards its output using
 *	ProcessOutput objects.
 **/
public class ProcessContainer
{
	/**
	 *	The Process that is run by this ProcessContainer.
	 **/
	private Process p;
	/**
	 *	The display control for things printed to stdout.
	 **/
	private ConsoleDisplay outputComponent;
	/**
	 *	The display control for things printed to stderr (which may be the same
	 *	as outputComponent).
	 **/
	private ConsoleDisplay errorComponent;
	/**
	 *	Output thread for stdout.
	 **/
	private ProcessOutput stdout;
	/**
	 *	Output thread for stderr.
	 **/
	private ProcessOutput stderr;
	/**
	 *	The exit value of this process.  In normal semantics, an exit value of
	 *	zero means the program exited normally, and anything else indicates an
	 *	error or crash.
	 **/
	private int exitVal;
	/**
	 *	This is true if the process has already exited.
	 **/
	private boolean done;
	
	/**
	 *	Creates a new ProcessContainer for p that forwards its standard
	 *	output/error streams into <code>output</code>.
	 *	
	 *	Note that it will clear output if it isn't already clear.
	 *	
	 *	This process will be forcibly killed according to the current user
	 *	settings.
	 **/
	public ProcessContainer(Process p, ConsoleDisplay output, ConsoleDisplay error)
	{
		this(p, output, error, true);
	}
	
	/**
	 *	Creates a new ProcessContainer for p that forwards its standard
	 *	output/error streams into <code>output</code>.
	 *	
	 *	Note that it will clear output if it isn't already clear.
	 *	
	 *	If doTimeout is true, the process will be killed according to the
	 *	current user settings for the time limit.
	 **/
	public ProcessContainer(Process p, ConsoleDisplay output, ConsoleDisplay error, boolean doTimeout)
	{
		
		this.p = p;
		outputComponent = output;
		errorComponent = error;
		if (doTimeout)
			new KillThread(this).start();
	}
	
	/**
	 *	Starts the threads that listen to the output and error streams of the
	 *	process.
	 **/
	public synchronized void start()
	{
		stdout = new ProcessOutput(p.getInputStream(), outputComponent);
		stderr = new ProcessOutput(p.getErrorStream(), outputComponent);
		stdout.start();
		stderr.start();
	}
	
	/**
	 *	Finishes and stores the exit value for the process.
	 **/
	public synchronized void waitFor()
	{
		try
		{
			exitVal = p.waitFor();
			done = true;
		}
		catch (InterruptedException ex)
		{
			outputComponent.println("***\nInterrupted***\n");
			errorComponent.println("***\nInterrupted***\n");
		}
	}
	
	/**
	 *	Returns true if this process has finished.
	 **/
	public synchronized boolean isDone()
	{
		return done || (stderr != null && stdout != null && stderr.isDone() && stdout.isDone());
	}
	
	/**
	 *	Forceably kills the process.
	 *	
	 *	You'll be glad sometimes that this option exists.
	 **/
	public void kill()
	{
		p.destroy();
	}
	
	/**
	 *	Returns the exit value of the process, waiting for it to finish if it
	 *	hasn't yet.
	 **/
	public int endVal()
	{
		if (!done)
			waitFor();
		if (done)
			return exitVal;
		return -1;
	}
	
	/**
	 *	Returns the display for stdout.
	 **/
	public ConsoleDisplay getStdDisplay()
	{
		return stdout.getOutputDisplay();
	}
	
	/**
	 *	Returns the display for stderr.
	 **/
	public ConsoleDisplay getErrDisplay()
	{
		return stderr.getOutputDisplay();
	}
}

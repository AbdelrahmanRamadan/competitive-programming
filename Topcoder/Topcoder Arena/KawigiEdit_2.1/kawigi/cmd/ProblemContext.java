package kawigi.cmd;
import kawigi.problem.*;
import kawigi.language.*;

/**
 *	This class is basically few globals that store the context of the current
 *	problem and language being worked on in KawigiEdit.
 **/
public class ProblemContext
{
	/**
	 *	ClassDecl describing the current problem.
	 **/
	private static ClassDecl currentClass;
	/**
	 *	EditorLanguage indicating the current language.
	 **/
	private static EditorLanguage currentLanguage;
	
	/**
	 *	Returns the current problem's class info.
	 **/
	public static ClassDecl getCurrentClass()
	{
		return currentClass;
	}
	
	/**
	 *	Sets the current problem's class info.
	 **/
	public static void setCurrentClass(ClassDecl currentClass)
	{
		ProblemContext.currentClass = currentClass;
	}
	
	/**
	 *	Returns the current language that is being used.
	 **/
	public static EditorLanguage getLanguage()
	{
		return currentLanguage;
	}
	
	/**
	 *	Sets the current language that is being used.
	 **/
	public static void setLanguage(EditorLanguage lang)
	{
		currentLanguage = lang;
	}
}

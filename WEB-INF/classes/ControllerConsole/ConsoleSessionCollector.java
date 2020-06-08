package ControllerConsole;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

import java.util.HashMap;
import java.util.Map;
import java.util.Iterator;
import java.util.Set;
import java.util.ArrayList;

public class ConsoleSessionCollector implements HttpSessionListener
{
	public ConsoleSessionCollector()
	{
	}

	@Override
	public void sessionCreated(HttpSessionEvent event) 
	{
		HttpSession session = event.getSession();
		ServletContext ctx = session.getServletContext(); 
		Map<String, HttpSession> sessions = (Map<String, HttpSession>)ctx.getAttribute("ConsoleSessions");
		sessions.put(session.getId(), session);
		//System.out.println("Session created " + session.getId());
	}

    	@Override
	public void sessionDestroyed(HttpSessionEvent event)
	{
		HttpSession session = event.getSession();
		ServletContext ctx = session.getServletContext(); 
		Map<String, HttpSession> sessions = (Map<String, HttpSession>)ctx.getAttribute("ConsoleSessions");
		sessions.remove(session.getId());
		//System.out.println("Session destroyed " + session.getId());
	}
}
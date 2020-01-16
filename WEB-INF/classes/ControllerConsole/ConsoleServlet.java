package ControllerConsole;

import java.io.IOException;
import java.sql.SQLException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletConfig;
import javax.servlet.http.HttpSession;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;

import ControllerConsole.User;

public class ConsoleServlet extends HttpServlet
{
	static Logger logger = LogManager.getLogger(ControllerConsole.ConsoleServlet.class);
	private ControllerConsole.Controller c;

	public void init(ServletConfig config) throws ServletException
	{
		super.init(config);

		c = new ControllerConsole.Controller();
		logger.info("Opening controller");
		int i = c.Open();
		switch (i)
		{
			case  0:logger.info("Controller opened");
				break; // success
			case -1:logger.info("Channels init failed");
				break; // channels init failed
			case -2:logger.info("Bits init failed");
				break; // bits init failed
			case -3:logger.info("Pulses init failed");
				break; // pulses init failed
		}
		
		getServletContext().setAttribute("controller", c);  
	}

	private boolean isAuthenticated(HttpServletRequest request)
	{
		ControllerConsole.User u;

		u = (ControllerConsole.User)request.getSession().getAttribute("user");
		if (u!=null)
		{
			if (u.isLoggedIn())
			{
				return(true);
			}
		}
		else
		{
			if (request.getLocalAddr().equals(request.getRemoteAddr()))
			{
				return(true);
			}
		}
		return(false);
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException  
	{
		ControllerConsole.User u;
		String username, password;
		int id, devid;
		byte value, v;
		
		if (request.getParameter("login")!=null)
		{
			u = new ControllerConsole.User();
			username = request.getParameter("username");
			password = request.getParameter("password");
			if (u.isPasswordValid(username, password))
			{
				request.getSession().setAttribute("user", u);
				request.getRequestDispatcher("console.jsp").forward(request, response);
			}
			else
			{
				request.getRequestDispatcher("loginfailed.jsp").forward(request, response);
			}
		}
		else if (request.getParameter("channel")!=null)
		{
			if (isAuthenticated(request))
			{
				id = Integer.parseInt(request.getParameter("id"));
				devid = Integer.parseInt(request.getParameter("devid"));
				value = (byte)Integer.parseInt(request.getParameter("value"));
				c.setChannelValue(id, value);
				c.writeChannel();
				v = c.getChannelValue(id);
				PrintWriter pw = response.getWriter();
				pw.printf("{ \"id\" : %d, \"value\" : %d, \"devid\" : %d }", id, v, devid);
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("bit")!=null)
		{
			if (isAuthenticated(request))
			{
				id = Integer.parseInt(request.getParameter("id"));
				devid = Integer.parseInt(request.getParameter("devid"));
				value = (byte)Integer.parseInt(request.getParameter("value"));
				c.setBitValue(id, value);
				v = c.getBitValue(id);
				PrintWriter pw = response.getWriter();
				pw.printf("{ \"id\" : %d, \"value\" : %d, \"devid\" : %d }", id, v, devid);
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("pulse")!=null)
		{
			if (isAuthenticated(request))
			{
				id = Integer.parseInt(request.getParameter("id"));
				devid = Integer.parseInt(request.getParameter("devid"));
				int duration = Integer.parseInt(request.getParameter("value"));
				c.pulseOut(id, duration);
				PrintWriter pw = response.getWriter();
				pw.printf("{ \"id\" : %d, \"value\" : %d, \"devid\" : %d }", id, duration, devid);
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("readchannel")!=null)
		{
			if (isAuthenticated(request))
			{
				id = Integer.parseInt(request.getParameter("id"));
				devid = Integer.parseInt(request.getParameter("devid"));
				c.readChannel();
				v = c.getInputChannelValue(id);
				PrintWriter pw = response.getWriter();
				pw.printf("{ \"id\" : %d, \"value\" : %d, \"devid\" : %d }", id, v, devid);
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("status")!=null)
		{
			PrintWriter pw = response.getWriter();
			pw.printf("{ \"status\" : \"%s\", \"version\" : %d, \"local\" : \"%s\", \"remote\" : \"%s\" }", "running", 0, request.getLocalAddr(), request.getRemoteAddr());
			pw.flush();
			pw.close();
		}
		if (request.getParameter("logout")!=null)
		{
			request.getSession().removeAttribute("user");
			request.getRequestDispatcher("login.jsp").forward(request, response);
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException  
	{
		doGet(request, response);
	}

	public void destroy()
	{
		getServletContext().removeAttribute("controller");
		c.Close();
		logger.info("Controller closed");
		super.destroy();
	}
}

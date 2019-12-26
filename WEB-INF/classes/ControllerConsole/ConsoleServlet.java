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

import ControllerConsole.User;

public class ConsoleServlet extends HttpServlet
{
	private ControllerConsole.Controller c;

	public void init(ServletConfig config) throws ServletException
	{
		super.init(config);
		int i = c.Open();
		switch (i)
		{
			case  0:
				break; // success
			case -1:
				break; // channels init failed
			case -2:
				break; // bits init failed
			case -3:
				break; // pulses init failed
		}
		
		getServletContext().setAttribute("Controller", c);  
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException  
	{
		ControllerConsole.User u;
		String username, password;
		int id;
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
			u = request.getSession().getAttribute("user");
			if (u!=null)
			{
				if (u.isLoggedIn())
				{
					id = request.getParameter("id");
					value = (byte)request.getParameter("value");
					c.setChannelValue(id, value);
					v = c.getChannelValue(id);
					PrintWriter pw = response.getWriter();
					pw.printf("{ \"id\" : %d, \"value\" : %d }", id, v);
					pw.flush();
					pw.close();
				}
			}
		}
		else if (request.getParameter("bit")!=null)
		{
			u = request.getSession().getAttribute("user");
			if (u!=null)
			{
				if (u.isLoggedIn())
				{
					id = request.getParameter("id");
					value = (byte)request.getParameter("value");
					c.setBitValue(id, value);
					v = c.getBitValue(id);
					PrintWriter pw = response.getWriter();
					pw.printf("{ \"id\" : %d, \"value\" : %d }", id, v);
					pw.flush();
					pw.close();
				}
			}
		}
		else if (request.getParameter("pulse")!=null)
		{
			u = request.getSession().getAttribute("user");
			if (u!=null)
			{
				if (u.isLoggedIn())
				{
					id = request.getParameter("id");
					c.pulseOut(id);
					PrintWriter pw = response.getWriter();
					pw.printf("{ \"id\" : %d }", id);
					pw.flush();
					pw.close();
				}
			}
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
		getServletContext().removeAttribute("Controller");
		c.Close();
	}
}  

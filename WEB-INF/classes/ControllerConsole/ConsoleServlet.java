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
	public void init(ServletConfig config) throws ServletException
	{
		super.init(config);
		// open controller
		// getServletContext().setAttribute("Controller", controller);  
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException  
	{
		if (request.getParameter("login")!=null)
		{
			ControllerConsole.User u = new ControllerConsole.User();
			String username = request.getParameter("username");
			String password = request.getParameter("password");
			if (u.isPasswordValid(username, password))
			{
				request.getSession().setAttribute("user", u);
				request.getRequestDispatcher("console.jsp").forward(request, response);
			}
			else
			{
/*
				PrintWriter pw = response.getWriter();
				pw.println(username + " " + password + " failed");
				pw.close();
*/
				request.getRequestDispatcher("loginfailed.jsp").forward(request, response);
			}
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException  
	{
		doGet(request, response);
	}

	public void destroy()
	{
		// getServletContext().removeAttribute("Controller");
		// close controller
	}
}  
package ControllerConsole;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Iterator;
import java.util.Set;

import java.io.IOException;
import java.io.PrintWriter;

import java.sql.SQLException;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletConfig;
import javax.servlet.http.HttpSession;

import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;

import ControllerConsole.User;
import ControllerConsole.Device;
import ControllerConsole.UserDevices;

public class ConsoleServlet extends HttpServlet
{
	static Logger logger = LogManager.getLogger(ControllerConsole.ConsoleServlet.class);
	private ControllerConsole.Controller c;
	private Map<String, HttpSession> ConsoleSessions;

	public void init(ServletConfig config) throws ServletException
	{
		super.init(config);

		ServletContext ctx = getServletContext();

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
		ctx.setAttribute("controller", c);
		
		ConsoleSessions = new HashMap<String, HttpSession>();
		ctx.setAttribute("ConsoleSessions", ConsoleSessions);
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
		PrintWriter pw;
		
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
				if (request.getParameter("value")!=null)
				{
					value = (byte)Integer.parseInt(request.getParameter("value"));
					c.setChannelValue(id, value);
					c.writeChannel();
				}
				v = c.getChannelValue(id);
				pw = response.getWriter();
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
				if (request.getParameter("value")!=null)
				{
					value = (byte)Integer.parseInt(request.getParameter("value"));
					c.setBitValue(id, value);
				}
				v = c.getBitValue(id);
				pw = response.getWriter();
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
				if (request.getParameter("value")!=null)
				{
					value = (byte)Integer.parseInt(request.getParameter("value"));
					c.pulseOut(id, (int)value*100000);
				}
				v = c.getPulseValue(id);
				pw = response.getWriter();
				pw.printf("{ \"id\" : %d, \"value\" : %d, \"devid\" : %d }", id, v, devid);
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
				pw = response.getWriter();
				pw.printf("{ \"id\" : %d, \"value\" : %d, \"devid\" : %d }", id, v, devid);
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("status")!=null)
		{
			pw = response.getWriter();
			pw.printf("{ \"status\" : \"%s\", \"version\" : %d, \"local\" : \"%s\", \"remote\" : \"%s\" }", "running", 0, request.getLocalAddr(), request.getRemoteAddr());
			pw.flush();
			pw.close();
		}
		else if (request.getParameter("logout")!=null)
		{
			request.getSession().removeAttribute("user");
			request.getRequestDispatcher("login.jsp").forward(request, response);
		}
		else if (request.getParameter("rlogin")!=null)
		{
			u = new ControllerConsole.User();
			username = request.getParameter("username");
			password = request.getParameter("password");
			if (u.isPasswordValid(username, password))
			{
				request.getSession().setAttribute("user", u);
				v = 1;
			}
			else
			{
				v = 0;
			}
			pw = response.getWriter();
			pw.printf("{ \"login\" : %d }", v);
			pw.flush();
			pw.close();
		}
		else if (request.getParameter("channels")!=null)
		{
			if (isAuthenticated(request))
			{
				pw = response.getWriter();
				ControllerConsole.User user = (ControllerConsole.User)request.getSession().getAttribute("user");
				ControllerConsole.UserDevices devices = new ControllerConsole.UserDevices();
				Iterator<Device> channelIter = devices.getDevicesOfUser(user, "A", 0, 7).iterator();
				String separator = "";
				pw.printf("{ \"devices\" : [ ");
				while (channelIter.hasNext())
				{
					Device dev = channelIter.next();
					pw.printf("%s{ \"service\" : \"channel\", \"level\" : \"%s\", \"devid\" : %d, \"dtext\" : \"%s\", \"chnnl\" : %d, \"dtype\" : %d, \"dttext\" : \"%s\", \"numstates\" : %d, \"initval\" : %d, \"categ\" : \"%s\", \"catxt\" : \"%s\", \"dicon\" : \"%s\", \"dticon\" : \"%s\" }", separator, dev.getAuthorizationLevel(), dev.getDeviceID(), dev.getDeviceText(), dev.getDeviceChannel(), dev.getDeviceType(), dev.getDeviceTypeText(), dev.getDeviceNumStates(), dev.getDeviceInitialValue(), dev.getDeviceCategory(), dev.getDeviceCategoryText(), dev.getDeviceIcon(), dev.getDeviceTypeIcon());
					separator = ", ";
				}
				pw.printf(" ] }");
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("bits")!=null)
		{
			if (isAuthenticated(request))
			{
				pw = response.getWriter();
				ControllerConsole.User user = (ControllerConsole.User)request.getSession().getAttribute("user");
				ControllerConsole.UserDevices devices = new ControllerConsole.UserDevices();
				Iterator<Device> channelIter = devices.getDevicesOfUser(user, "A", 8, 9).iterator();
				String separator = "";
				pw.printf("{ \"devices\" : [ ");
				while (channelIter.hasNext())
				{
					Device dev = channelIter.next();
					pw.printf("%s{ \"service\" : \"bit\", \"level\" : \"%s\", \"devid\" : %d, \"dtext\" : \"%s\", \"chnnl\" : %d, \"dtype\" : %d, \"dttext\" : \"%s\", \"numstates\" : %d, \"initval\" : %d, \"categ\" : \"%s\", \"catxt\" : \"%s\", \"dicon\" : \"%s\", \"dticon\" : \"%s\" }", separator, dev.getAuthorizationLevel(), dev.getDeviceID(), dev.getDeviceText(), dev.getDeviceChannel(), dev.getDeviceType(), dev.getDeviceTypeText(), dev.getDeviceNumStates(), dev.getDeviceInitialValue(), dev.getDeviceCategory(), dev.getDeviceCategoryText(), dev.getDeviceIcon(), dev.getDeviceTypeIcon());
					separator = ", ";
				}
				pw.printf(" ] }");
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("pulses")!=null)
		{
			if (isAuthenticated(request))
			{
				pw = response.getWriter();
				ControllerConsole.User user = (ControllerConsole.User)request.getSession().getAttribute("user");
				ControllerConsole.UserDevices devices = new ControllerConsole.UserDevices();
				Iterator<Device> channelIter = devices.getDevicesOfUser(user, "A", 10, 11).iterator();
				String separator = "";
				pw.printf("{ \"devices\" : [ ");
				while (channelIter.hasNext())
				{
					Device dev = channelIter.next();
					pw.printf("%s{ \"service\" : \"pulse\", \"level\" : \"%s\", \"devid\" : %d, \"dtext\" : \"%s\", \"chnnl\" : %d, \"dtype\" : %d, \"dttext\" : \"%s\", \"numstates\" : %d, \"initval\" : %d, \"categ\" : \"%s\", \"catxt\" : \"%s\", \"dicon\" : \"%s\", \"dticon\" : \"%s\" }", separator, dev.getAuthorizationLevel(), dev.getDeviceID(), dev.getDeviceText(), dev.getDeviceChannel(), dev.getDeviceType(), dev.getDeviceTypeText(), dev.getDeviceNumStates(), dev.getDeviceInitialValue(), dev.getDeviceCategory(), dev.getDeviceCategoryText(), dev.getDeviceIcon(), dev.getDeviceTypeIcon());
					separator = ", ";
				}
				pw.printf(" ] }");
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("sensors")!=null)
		{
			if (isAuthenticated(request))
			{
				pw = response.getWriter();
				ControllerConsole.User user = (ControllerConsole.User)request.getSession().getAttribute("user");
				ControllerConsole.UserDevices devices = new ControllerConsole.UserDevices();
				Iterator<Device> channelIter = devices.getDevicesOfUser(user, "S", 0, 7).iterator();
				String separator = "";
				pw.printf("{ \"devices\" : [ ");
				while (channelIter.hasNext())
				{
					Device dev = channelIter.next();
					pw.printf("%s{ \"service\" : \"readchannel\", \"level\" : \"%s\", \"devid\" : %d, \"dtext\" : \"%s\", \"chnnl\" : %d, \"dtype\" : %d, \"dttext\" : \"%s\", \"numstates\" : %d, \"initval\" : %d, \"categ\" : \"%s\", \"catxt\" : \"%s\", \"dicon\" : \"%s\", \"dticon\" : \"%s\" }", separator, dev.getAuthorizationLevel(), dev.getDeviceID(), dev.getDeviceText(), dev.getDeviceChannel(), dev.getDeviceType(), dev.getDeviceTypeText(), dev.getDeviceNumStates(), dev.getDeviceInitialValue(), dev.getDeviceCategory(), dev.getDeviceCategoryText(), dev.getDeviceIcon(), dev.getDeviceTypeIcon());
					separator = ", ";
				}
				pw.printf(" ] }");
				pw.flush();
				pw.close();
			}
		}
		else if (request.getParameter("rlogout")!=null)
		{
			request.getSession().removeAttribute("user");
			v = 0;
			pw = response.getWriter();
			pw.printf("{ \"login\" : %d }", v);
			pw.flush();
			pw.close();
		}
		else if (request.getParameter("sessions")!=null)
		{
			u = (ControllerConsole.User)request.getSession().getAttribute("user");
			if (u!=null)
			{
				if (u.isSuperUser())
				{
					pw = response.getWriter();

					String sessionId = request.getSession().getId();
					ServletContext ctx = getServletContext(); 
					Map<String, HttpSession> sessions = (Map<String, HttpSession>)ctx.getAttribute("ConsoleSessions");

					Set set = sessions.entrySet();
      					Iterator iterator = set.iterator();

					String separator = "";
					pw.printf("{ \"sessions\" : [ ");
					while (iterator.hasNext())
					{
						Map.Entry mentry = (Map.Entry)iterator.next();
						HttpSession session = (HttpSession)mentry.getValue();
						u = (ControllerConsole.User)session.getAttribute("user");
						String uname = (u!=null?u.getUserName():""); 
						pw.printf("%s{ \"id\" : \"%s\", \"maxinactiveinterval\" : %d, \"username\" : \"%s\" }", separator, mentry.getKey(), session.getMaxInactiveInterval(), uname);
						separator = ", ";
					}
					pw.printf(" ] }");
					pw.flush();
					pw.close();
				}
			}
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
package ControllerConsole;

import java.util.ArrayList;
import java.util.ResourceBundle;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.DriverManager;
import java.sql.SQLException;

public class User
{
	private String username;
	private boolean superuser;

	private ResourceBundle rb;
	private String DBpath;

	public User()
	{
		rb = ResourceBundle.getBundle("ControllerConsole.Global");
		DBpath = rb.getString("ControllerConsole.DBPATH");

		superuser = false;
		username = "";
	}

	public String getUserName()
	{
		return(username);
	}

	public boolean isPasswordValid(String user, String pass)
	{
		Connection conn = null;
		ResultSet rs = null;
		Statement stat = null;
		int count = 0;

		superuser = false;

		try
		{
			Class.forName("org.sqlite.JDBC");
		}
		catch (ClassNotFoundException ex)
		{
			//throw ex;
		}

		try
		{
			conn = DriverManager.getConnection("jdbc:sqlite:" + DBpath);
			stat = conn.createStatement();
			rs = stat.executeQuery("select * from users where username='" + user + "' and password = '" + pass + "';");
			while (rs.next()) 
			{
				superuser = Integer.parseInt(rs.getString("superuser")) > 0;
				username = user;
				count++;
				break;
			}
			rs.close();
			stat.close();
			conn.close();
		}
		catch(SQLException sqlex)
		{
        		//throw sqlex;	
		}

		return(count>0);
	}

	public boolean isLoggedIn()
	{
		return(!username.equals(""));
	}

	public boolean isSuperUser()
	{
		return(superuser);
	}

	public void logout()
	{
		superuser = false;
		username = "";
	}
}
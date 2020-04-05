<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
<link rel="icon" type="image/png" href="images/controller.png">
</head>

<body onload="javascript:load()">
<form name="loginform" method="POST" action="ControllerConsole?login">
<table align="center">
 <tr>
  <td colspan="2" align="center"><img width="128px" height="128px" src="images/controller.png"/></td>
 </tr>
 <tr>
  <td colspan="2" align="center"><font style="font-name:Arial;font-size:36pt;"><b>IOBoard V0 Controller Console</b></font></td>
 </tr>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt;"><b>User name</b></font></td>
  <td><input style="font-name:Arial;font-size:24pt;" type="text" name="username" /></td>
 </tr>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt;"><b>Password</b></font></td>
  <td><input style="font-name:Arial;font-size:24pt;" type="password" name="password" /></td>
 </tr>
 <tr>
  <td></td>
  <td><br><input style="font-name:Arial;font-size:36pt;width:256px;height:128px;" type="submit" name="login" value="Login" /></td>
 </tr>
</table>
</form>
</body>
</html>

<script type="text/javascript">
function load()
{
 loginform.username.focus();
}
</script>
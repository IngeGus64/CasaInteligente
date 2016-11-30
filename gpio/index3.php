<html>
<head>
<?php 
if (isset($_POST['RedON']))
{
exec('sudo python /var/www/red_on.py');
}
if (isset($_POST['RedOFF']))
{
exec('sudo python /var/www/red_off.py');
}
if (isset($_POST['YellowON']))
{
exec('sudo python /var/www/gpio/yellow_on.py');
}
if (isset($_POST['YellowOFF']))
{
exec('sudo python /var/www/gpio/yellow_off.py');
}
if (isset($_POST['GreenON']))
{
exec('sudo python /var/www/gpio/green_on.py');
}
if (isset($_POST['GreenOFF']))
{
exec('sudo python /var/www/gpio/green_off.py');
}
?>

  <title></title>
</head>
<body>
<form method="post">
  <table
 style="width: 75%; text-align: left; margin-left: auto; margin-right: auto;"
 border="0" cellpadding="2" cellspacing="2">
    <tbody>
      <tr>
        <td style="text-align: center;">Turn LED on</td>
        <td style="text-align: center;">Turn LED off</td>
  </tr>
  <tr>
    <td style="text-align: center;"><button name="RedON">Red On</button></td>
    <td style="text-align: center;"><button name="RedOFF">Red Off</button></td>
  </tr>
  <tr>
    <td style="text-align: center;"><button name="YellowON">Yellow On</button></td>
    <td style="text-align: center;"><button name="YellowOFF">Yellow Off</button></td>
  </tr>
  <tr>
    <td style="text-align: center;"><button name="GreenON">Green On</button></td>
    <td style="text-align: center;"><button name="GreenOFF">Green Off</button></td>
  </tr>
</tbody>
  </table>
</form>
</body>
</html>

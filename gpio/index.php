<html>
 <head>
 <meta charset="UTF-8" />
 <title>CASA INTELIGENTE </title>
                        <!--index.php--> 
 </head>
 <body>
  <h2> SERVICIOS ELECTRONICOS</h2>
  
  <h3> <p>Control remoto de puertos digitales de entrada y de salida </p> </h3>
  
  <div class="container">
    <header><br>
		<h4>CONTROL REMOTO DE UN LED CON RASPBERRY PI</H4>
		<hr>
    </header>
    <section>
	<br><br>
	<input type="checkbox" id="switch" name="switch">
	<label for="switch" class="switch"></label>
	<div align="center" id="bombillo">
	</div>
    </section>
  </div>
  <script>
	$("#switch").change(function()
	{
	   var chequeado=$("#switch").attr("checked");
	   if(chequeado) {
		$("#switch").removeAttr("checked");
		console.log("estado 1");
		var estado=1;
		$("#bombillo").text(("Estado apagado");
		$("#bombillo").removeClass('alert alert-info').addClass("alert alert-danger");
		$("#imagen_bombillo").html('img src="images/off.jpg">'};
		$.ajax({
			data:{valor_estado: estado},
			url:'procesa.php',
			type:'POST',
			success: function(response){
				//alert("Salida: "+response);
			}
		});
	}
	else {
		$("#switch").attr("checked","checked");
		console.log(("estado_2");
		var estado=2;
		$("#bombillo").text(("Estado encendido");
                $("#bombillo").removeClass('alert alert-danger').addClass("alert alert-info");
                $("#imagen_bombillo").html('img src="images/on.jpg">'};
		$.ajax({
                        data:{valor_estado: estado},
                        url:'procesa.php',
                        type:'POST',
                        success: function(response){
                                //alert("Salida: "+response);
                        }
                });
	}
  });
  </script>

  <hr><br>
  <!--GPIO5--> 
  <form action="" method="post">
   GPIO 05&nbsp;<input type="submit" name="encender5" value="Encender">
   <input type="submit" name="apagar5" value="Apagar">
   <input type="submit" name="parpadear5" value="Parpadear">
 <br></br>

  <!--GPIO16-->
  <form action="" method="post">
   GPIO 16&nbsp;<input type="submit" name="activar16" value="Activa">
   <br></br>

  <!--GPIO17--> 
  <form action="" method="post">
   GPIO 17&nbsp;<input type="submit" name="encender17" value="Encender">
   <input type="submit" name="apagar17" value="Apagar">
   <input type="submit" name="parpadear17" value="Parpadear">
 <br></br>

  <!--GPI22--> 
  <form action="" method="post">
   GPIO 22&nbsp;<input type="submit" name="encender22" value="Encender">
   <input type="submit" name="apagar22" value="Apagar">
   <input type="submit" name="parpadear22" value="Parpadear">

 <br></br>

  <!--GPI23--> 
  <form action="" method="post">
   GPIO 23&nbsp;<input type="submit" name="encender23" value="Encender">
   <input type="submit" name="apagar23" value="Apagar">
   <input type="submit" name="parpadear23" value="Parpadear">

 <br></br>

  <!--GPI24--> 
  <form action="" method="post">
   GPIO 24&nbsp;<input type="submit" name="encender24" value="Encender">
   <input type="submit" name="apagar24" value="Apagar">
   <input type="submit" name="parpadear24" value="Parpadear">

 <br></br>


  <!--GPIO27--> 
  <form action="" method="post">
   GPIO 27&nbsp;<input type="submit" name="encender27" value="Encender">
   <input type="submit" name="apagar27" value="Apagar">
   <input type="submit" name="parpadear27" value="Parpadear">

 <br></br>
 <br></br>
 <p>Ing. Gustavo Rojas Bravo </p>
 <p>Paola del Carmen Rojas Escobedo </p>
 <p>Paulina Rojas Escobedo </p>

 </body>
</html>

<?php

// Funciones PHP del pin GPIO 5

  if ($_POST[encender5]) { 
   $a- exec("sudo python /var/www/html/gpio/5/enciende.py");
   echo $a;
  }

  if ($_POST[apagar5]) { 
   $a- exec("sudo python /var/www/html/gpio/5/apaga.py");
   echo $a;
  }

  if ($_POST[parpadear5]) { 
   $a- exec("sudo python /var/www/html/gpio/5/parpadea.py");
   echo $a;
  }

// Fin de las funciónes del pin GPIO 5
  if ($_POST[activar16]) { 
   $a- exec("sudo python /var/www/html/gpio/16/input16.py");
   echo $a;
  }

//  if (!$_POST[encender5]) {
//   $a- exec("sudo python /var/www/html/gpio/16/input16.py")
//   echo $a;
//  }

// Funciones PHP del pin GPIO 17

  if ($_POST[encender17]) { 
   $a- exec("sudo python /var/www/html/gpio/17/enciende.py");
   echo $a;
  }

  if ($_POST[apagar17]) { 
   $a- exec("sudo python /var/www/html/gpio/17/apaga.py");
   echo $a;
  }

  if ($_POST[parpadear17]) { 
   $a- exec("sudo python /var/www/html/gpio/17/parpadea.py");
   echo $a;
  }

// Fin de las funciónes del pin GPIO 17

// Funciones PHP del pin GPIO 22

  if ($_POST[encender22]) { 
   $a- exec("sudo python /var/www/html/gpio/22/enciende.py");
   echo $a;
  }

  if ($_POST[apagar22]) { 
   $a- exec("sudo python /var/www/html/gpio/22/apaga.py");
   echo $a;
  }

  if ($_POST[parpadear22]) { 
   $a- exec("sudo python /var/www/html/gpio/22/parpadea.py");
   echo $a;
  }

// Fin de las funciónes del pin GPIO 22

// Funciones PHP del pin GPIO 23

  if ($_POST[encender23]) { 
   $a- exec("sudo python /var/www/html/gpio/23/enciende.py");
   echo $a;
  }

  if ($_POST[apagar23]) { 
   $a- exec("sudo python /var/www/html/gpio/23/apaga.py");
   echo $a;
  }

  if ($_POST[parpadear23]) { 
   $a- exec("sudo python /var/www/html/gpio/23/parpadea.py");
   echo $a;
  }

// Fin de las funciónes del pin GPIO 23

// Funciones PHP del pin GPIO 24

  if ($_POST[encender24]) { 
   $a- exec("sudo python /var/www/html/gpio/24/enciende.py");
   echo $a;
  }

  if ($_POST[apagar24]) { 
   $a- exec("sudo python /var/www/html/gpio/24/apaga.py");
   echo $a;
  }

  if ($_POST[parpadear24]) { 
   $a- exec("sudo python /var/www/html/gpio/24/parpadea.py");
   echo $a;
  }

// Fin de las funciónes del pin GPIO 24


// Funciones PHP del pin GPIO 27

  if ($_POST[encender27]) { 
   $a- exec("sudo python /var/www/html/gpio/27/enciende.py");
   echo $a;
  }

  if ($_POST[apagar27]) { 
   $a- exec("sudo python /var/www/html/gpio/27/apaga.py");
   echo $a;
  }

  if ($_POST[parpadear27]) { 
   $a- exec("sudo python /var/www/html/gpio/27/parpadea.py");
   echo $a;
  }

// Fin de las funciónes del pin GPIO 27


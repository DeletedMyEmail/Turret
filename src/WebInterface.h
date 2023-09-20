const char* PAGE_HTML = R"=====(
  
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<title>Turret Interface</title>
    <style>
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
    .coords {
      position: fixed;
      height: 30px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 10px;
      font-weight: bold;
      line-height: 30px;
      padding-right: 8px;
    }
    
  </style>

<body style="background-color: #efefef">
  
    <header>
      <div class="navbar">
          <div class="navtitle">Turret Interface</div>  
      </div>
    </header>

    <div class="coords" id="coords">
      <div id="x">x: 0°</div>
      <div id="y">y: 0°</div>
    </div>
  
</body>


<script type = "text/javascript">
    document.getElementById("coords").setAttribute("style", "left: " + (window.innerWidth/2+15) + "px; top: " + (window.innerHeight/2-15) + "px");

    window.addEventListener("mousemove", function(event) {
        const x = event.clientX
        const y = event.clientY 
        
        const x_degrees = (x / window.innerWidth) * 180 - 90
        const y_degrees = -((y / window.innerHeight) * 180 - 90)

        document.getElementById("coords").setAttribute("style", "left: " + (x+15) + "px; top: " + (y-15) + "px");
        document.getElementById("x").innerHTML = "x: " + Math.round(x_degrees) + "°"
        document.getElementById("y").innerHTML = "y: " + Math.round(y_degrees) + "°"

        sendCoordinates(x_degrees+90, y_degrees+90);
    });

    window.addEventListener("click", function(event) {
        console.log("FIRE")
        fire();
    });

    function fire() {
      var xhttp = new XMLHttpRequest() 
       
      xhttp.open("PUT", "fire", false)
      xhttp.send()
    }

    function enableAutoMode(value) {
      var xhttp = new XMLHttpRequest() 
      xhttp.open("PUT", "auto_mode", value)
      xhttp.send()
    }
    
    function sendCoordinates(x, y) {
      console.log("X: " + x + " Y: " + y)
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "move?VALUE={x:" + x + ", y:" + y + "}", true);
      xhttp.send();
    }
  </script>
</html>
)=====";
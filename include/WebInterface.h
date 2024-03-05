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
    .movement-area {
      position: absolute;
      width: 80vw;
      height: 70vh;
      left: 10vw;
      top: 20vh;
      border: #3a3c48 3px solid;
      cursor: crosshair;
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
    <div class="movement-area" id="move-area">
      <div class="coords" id="coords">
        <div id="x">x: 0°</div>
        <div id="y">y: 0°</div>
      </div>  
    </div>
    
</body>


<script type = "text/javascript">
    document.getElementById("coords").setAttribute("style", "left: " + (window.innerWidth/2+15) + "px; top: " + (window.innerHeight/2-15) + "px");

    var time = Date.now()
    window.addEventListener("mousemove", function(event) {
        const x = event.clientX
        const y = event.clientY 
      
        const rect = document.getElementById("move-area").getBoundingClientRect(); 
        var xPosition = x - rect.left - rect.width / 2; 
        var yPosition = y - rect.top - rect.height / 2;

        if (xPosition < -rect.width / 2 || xPosition > rect.width / 2 || yPosition > rect.height / 2 || yPosition < -rect.height / 2) {
          return
        }   

        const x_degrees = (xPosition / rect.width) * 180
        const y_degrees = (yPosition / rect.height) * -180

        document.getElementById("coords").setAttribute("style", "left: " + (x+15) + "px; top: " + (y-15) + "px");
        document.getElementById("x").innerHTML = "x: " + Math.round(x_degrees) + "°"
        document.getElementById("y").innerHTML = "y: " + Math.round(y_degrees) + "°"
    
        if (Date.now() - time < 80) {
          return
        }
        time = Date.now()    
 
        sendCoordinates(x_degrees+90, y_degrees+90);
    });

    window.addEventListener("click", function(event) {
        fire();
    });

    function fire() {
      var xhttp = new XMLHttpRequest() 
       
      xhttp.open("PUT", "fire", true)
      xhttp.send()
    }

    function enableAutoMode(value) {
      var xhttp = new XMLHttpRequest() 
      xhttp.open("PUT", "auto_mode", value)
      xhttp.send()
    }
    
    function sendCoordinates(x, y) {
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "move?VALUE={x:" + x + ", y:" + y + "}", true);
      xhttp.send();
    }
  </script>
</html>
)=====";
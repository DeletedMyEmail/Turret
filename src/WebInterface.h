const char* PAGE_HTML = R"=====(
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<title>Turret Interface</title>
    <style>
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
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
    
  </style>

<body style="background-color: #efefef">
  
    <header>
      <div class="navbar fixed-top">
          <div class="navtitle">Turret Interface</div>  
      </div>
    </header>
  
    <main class="container" style="margin-top:70px; height: 100vh;" >
        
    </main>

</body>


<script type = "text/javascript">
    const throttle = 500
    const start = (new Date).getTime()
    let last = (new Date).getTime()

    window.addEventListener("mousemove", function(event) {
        const now = (new Date).getTime()

        if ((now - last) < throttle) {
            return
        }
        last = now

        var x = event.clientX * (180 / window.innerWidth)
        var y = event.clientY * (180 / window.innerHeight)
        
        sendCoordinates(Math.round(x), Math.round(y));
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
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "move?VALUE={x:" + x + ", y:" + y + "}", true);
      xhttp.send();
    }
  </script>
</html>
)=====";
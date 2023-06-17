const char* PAGE_HTML = R"=====(
    <!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<title>Turret Interface</title>
    <style>
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
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
  
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    
  </style>

<body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="navtitle">Turret Interface</div>  
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
        <br>
        <div class="bodytext">Horizontal Rotation<span id="fanrpm"></span></div>
        <br>
        <input type="range" class="fanrpmslider" min="0" max="180" value = "0" step="1" width = "0%" oninput="hRotate(this.value)"/>
        <br>
        <div class="bodytext">Vertical Rotation<span id="fanrpm"></span></div>
        <br>
        <input type="range" class="fanrpmslider" min="0" max="180" value = "0" step="1" width = "0%" oninput="vRotate(this.value)"/>
        <br>
        <button onclick="fireButton()">Fire</button>
        <br>
        <Radio onclick="autoButton()">Auto-Mode</Radio>
    </main>

</body>


<script type = "text/javascript">
    function fireButton() {
      var xhttp = new XMLHttpRequest(); 
       
      xhttp.open("PUT", "fire", false);
      xhttp.send();
    }

    function autoButton(value) {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "auto_mode", value);
      xhttp.send(); 
    }
    
    function hRotate(value) {
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "h_pos?VALUE="+value, true);
      xhttp.send();
    }

    function vRotate(value) {
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "v_pos?VALUE="+value, true);
      xhttp.send();
    }
  </script>
</html>
)=====";
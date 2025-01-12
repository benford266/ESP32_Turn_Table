// HTML text page
const char HTMLTEXT[] = R"(<!DOCTYPE html>
<html lang="en">
 <head>
 <title>ESP32 Turn Table</title>
 <meta charset="UTF-8">
 <meta name="viewport" content="width=device-width, initial-scale=1">
 <style>
 body {
 font-family: Arial, sans-serif;
 color:rgb(255, 255, 255);
 background-color: #454444;
 display: flex;
 flex-flow: column;
 align-items: center;
 }
 shape {
 display: flex;
 flex-flow: column;
 align-items: center;
 }
 .flex container {
 display: flex;
 flex-flow: row;
 max-width: 30em;
 align-items: center;
 }
 @media all and (width <= 20em) {
 .flex container {
 display: flex;
 flex-flow: column;
 max-width: 45em;
 align-items: center;
 }
 }
 .flex-item {
 border: 1px solid;
 border-color:rgb(104, 104, 104);
 width: 120%;
 margin: .2em;
 padding: .1em;
 text-align: center;
 <1background: #ffffff;>
 }
 input {
 font-size: 1em;
 width: 49%;
 background-color: #adff2f;
 }

 </style>
 <script type="text/javascript">
 function updateStep(c) {
 if(c.value >= 5000) {
 if(c.step != 100) {
 c.step = 100;
 }
 } else if(c.value >= 500) {
 if(c.step != 10) {
 c.step = 10;
 }
 } else {
 if(c.step != 1) c.step = 1;
 }
 }
 </script>
 </head>
 <body>
 <h2>ESP32 Turn Table</h2>
 <h4>BFG</h3>
 <form action="/stepper">
 <div class="flex-container">
 <p class="flex-item">
 <label>
 <input style="width:6em; background-color:white" max="50000" min="0" name="speed" type="number" value="%ld" onchange="updateStep(this) "/ > 
 </label>
 <input name="setSpeed" type="submit" value="Set Speed Steps/Sec">
 </p>
 <p class="flex-item">
 <label>
 <input style="width:6em; background-color:white" max="160000" min="0" name="ramp" type="number" value="%ld" onchange="updateStep(this) " / > <label></label>
 </label>
 <input name="setRamp" type="submit" value="Set ramp">
 </p>
 </div>
 <div class="flex-container">
 <p class="flex-item">
 <input name="left" type="submit" value="1 Rotation Left">
 <input name="contl" type="submit" value="Spin Left">
 </p>
 <p class="flex-item">
 <input name="right" type="submit" value="1 Rotation Right">
 <input name="contr" type="submit" value="Spin Right ">
 </p>
 </div>
 <div class="flex-container">
 <p class="flex-item"><input style="background-color:red" name="stop" type="submit" value="Stop"></p>
 </div>
 </form>
</body>
</html>)";
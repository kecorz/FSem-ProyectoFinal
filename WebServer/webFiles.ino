// This function returns the JavaScript code required for the website:
String getJS()
{
  String css = R"(
  function showClock() {
  var clockElement = document.getElementById('clock');

  function updateClock(clock) {
    clock.innerHTML = new Date().toLocaleTimeString();
  }

  setInterval(function () {
    updateClock(clockElement);
  }, 1000);
  }
  
  showClock();
  
  $(document).ready(function () {
    $('.timepicker').timepicker();
    $('.timepicker').attr('onfocus', 'blur();');
  });

  )";
  return css;
}

// This function returns the CSS code required for the website:
String getCSS()
{
  String css = R"(
.offButton {
  background-color: red;
}

.closeButton {
  background-color: red;
}


  )";
  return css;
}

// Thie function returns the html code required for the website:
String getHTML()
{
  String html = R"(
  <!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Smart Home</title>
    <link
      href="https://fonts.googleapis.com/icon?family=Material+Icons"
      rel="stylesheet"
    />
    <link
      rel="stylesheet"
      href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css"
    />
    <style>
    )";

  html += getCSS();

  html += R"(
    </style>
    <link
      href="smartHub.css"
      type="text/css"
      rel="stylesheet"
      media="screen,projection"
    />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  </head>
  <body>
    <nav class="nav-extended">
      <div class="nav-wrapper container">
        <a href="#" class="brand-logo center">My Home</a>
      </div>
      <div class="nav-content">
        <ul class="tabs tabs-transparent">
          <li class="tab"><a class="active" href="#test1">Control</a></li>
          <li class="tab"><a href="#test2">Cameras</a></li>
        </ul>
      </div>
    </nav>

    <div class="container">
      <div class="section">
        <div class="row">
        )";

  if (doorbell)
  {
    html += R"(
        <div class="col s12 center">
            <div class="chip">
              Someone is at the door
              <i class="close material-icons">close</i>
            </div>
          </div>
          )";
  }

  html += R"(
          <h3 id="clock" class="col s12 center"></h3>
        </div>
        <div class="row">
          <div class="col s12 center">
            <h4>Temperature: )";

  html += temperature;

  html += R"( °C</h4>
          </div>
        </div>
        <div class="row">
          <div class="col s12 center">
            <h4>Garage door</h4>
          </div>
        </div>
        <div class="row">
          <div class="col s12 center">
          )";

  if (garageDoorOpen)
  {
    html += R"(
            <a href="/garageClose">
              <button class="btn waves-effect waves-light closeButton">
                Close
              </button>
            </a>
    )";
  }
  else
  {
    html += R"(
            <a href="/garageOpen">
              <button class="btn waves-effect waves-light openButton">
                Open
              </button>
            </a>
    )";
  }

  html += R"(
          </div>
        </div>
        <div class="row">
          <div class="col s12 center">
            <h4>Light System</h4>
          </div>
        </div>)";

  if (lightsOn)
  {
    html += R"(
      <div class="row">
          <div class="col s12 center">
            <a href="/lightsOff">
              <button class="btn waves-effect waves-light offButton">
                Lights Off
              </button>
            </a>
          </div>
        </div>
    )";
  }
  else
  {
    html += R"(
      <div class="row">
          <div class="col s12 center">
            <a href="/lightsOn">
              <button class="btn waves-effect waves-light onButton">
                Lights On
              </button>
            </a>
          </div>
        </div>
    )";
  }

  html += R"(  
        <div class="row">
          <form class="col s12" action="/get">
            <div class="row">
              <h5>Light intensity</h5>
              <div class="input-field col s10">
                <p class="range-field">
                  <input type="range" name="lightIntensity" id="test5" min="0" max="100" />
                </p>
              </div>
              <div class="input-field col s2">
                <button
                  class="btn waves-effect waves-light"
                  type="submit"
                  name="action"
                >
                  Set
                </button>
              </div>
            </div>
          </form>
          <form class="col s12" action="/get">
            <div class="row">
              <h5>Turn-on time: )";

  if (setLightOn)
  {
    html += String(selectedLightOnTime[0]) + ":" + String(selectedLightOnTime[1]) + " ";
    if (selectedLightOnTime[2] == 0)
    {
      html += "AM";
    }
    else
    {
      html += "PM";
    }
  }

  html += R"(
              </h5>
              <div class="input-field col s10">
                <input
                  id="turn-on-time"
                  type="text"
                  class="timepicker"
                  name="timeLightOnInput"
                />
              </div>
              <div class="input-field col s2">
                <button
                  class="btn waves-effect waves-light"
                  type="submit"
                  name="action"
                >
                  Set
                </button>
              </div>
            </div>
            <div class="row">
              <h5>Turn-off time: )";

  if (setLightOff)
  {
    html += String(selectedLightOffTime[0]) + ":" + String(selectedLightOffTime[1]) + " ";
    if (selectedLightOffTime[2] == 0)
    {
      html += "AM";
    }
    else
    {
      html += "PM";
    }
  }

  html += R"(
              </h5>
              <div class="input-field col s10">
                <input
                  id="turn-off-time"
                  type="text"
                  class="timepicker"
                  name="timeLightOffInput"
                />
              </div>
              <div class="input-field col s2">
                <button
                  class="btn waves-effect waves-light"
                  type="submit"
                  name="action"
                >
                  Set
                </button>
              </div>
            </div>
          </form>
        </div>
      </div>
    </div>

      <script
        src='https://code.jquery.com/jquery-3.5.1.slim.js'
        integrity='sha256-DrT5NfxfbHvMHux31Lkhxg42LY6of8TaYyK50jnxRnM='
        crossorigin='anonymous'
      ></script>
      <script>)";

  html += getJS();

  html +=
      R"(</script>
      <script src='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js'></script>
    </body>
  </html>
  )";
  return html;
}

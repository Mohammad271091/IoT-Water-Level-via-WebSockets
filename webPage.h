const char webpageCode[] PROGMEM =
    R"=====(

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Water Level Control</title>
    <style>
        *,
        *:before,
        *:after {
            box-sizing: border-box;
            outline: none;
        }

        body {
            background: #020438;
            font: 14px/1 "Open Sans", helvetica, sans-serif;
            -webkit-font-smoothing: antialiased;
        }

        .box {
            height: 27rem;
            width: 18rem;
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            background: #020438;
            border: solid white;
            border-top: 0;
            border-radius: 5%;
            /*change to make it circular */
            overflow: hidden;
        }

        .box .percent {
            position: absolute;
            left: 0;
            top: 0;
            z-index: 3;
            width: 100%;
            height: 100%;
            display: flex;
            display: -webkit-flex;
            align-items: center;
            justify-content: center;
            color: #fff;
            font-size: 64px;
        }

        .box .water {
            position: absolute;
            left: 0;
            top: 0;
            z-index: 2;
            width: 100%;
            height: 100%;
            transform: translate(0, 100%);
            background: #4d6de3;
            transition: all 5s; /*change for the water transition speed*/
        }

        .box .water_wave {
            width: 200%;
            position: absolute;
            bottom: 100%;
        }

        .box .water_wave_back {
            right: 0;
            fill: #c7eeff;
            -webkit-animation: wave-back 1.4s infinite linear;
            animation: wave-back 1.4s infinite linear;
        }

        .box .water_wave_front {
            left: 0;
            fill: #4d6de3;
            margin-bottom: -1px;
            -webkit-animation: wave-front 0.7s infinite linear;
            animation: wave-front 0.7s infinite linear;
        }

        @-webkit-keyframes wave-front {
            100% {
                transform: translate(-50%, 0);
            }
        }

        @keyframes wave-front {
            100% {
                transform: translate(-50%, 0);
            }
        }

        @-webkit-keyframes wave-back {
            100% {
                transform: translate(50%, 0);
            }
        }

        @keyframes wave-back {
            100% {
                transform: translate(50%, 0);
            }
        }
    </style>
</head>

<body>
    <svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
        style="display: none;">
        <symbol id="wave">
            <path
                d="M420,20c21.5-0.4,38.8-2.5,51.1-4.5c13.4-2.2,26.5-5.2,27.3-5.4C514,6.5,518,4.7,528.5,2.7c7.1-1.3,17.9-2.8,31.5-2.7c0,0,0,0,0,0v20H420z">
            </path>
            <path
                d="M420,20c-21.5-0.4-38.8-2.5-51.1-4.5c-13.4-2.2-26.5-5.2-27.3-5.4C326,6.5,322,4.7,311.5,2.7C304.3,1.4,293.6-0.1,280,0c0,0,0,0,0,0v20H420z">
            </path>
            <path
                d="M140,20c21.5-0.4,38.8-2.5,51.1-4.5c13.4-2.2,26.5-5.2,27.3-5.4C234,6.5,238,4.7,248.5,2.7c7.1-1.3,17.9-2.8,31.5-2.7c0,0,0,0,0,0v20H140z">
            </path>
            <path
                d="M140,20c-21.5-0.4-38.8-2.5-51.1-4.5c-13.4-2.2-26.5-5.2-27.3-5.4C46,6.5,42,4.7,31.5,2.7C24.3,1.4,13.6-0.1,0,0c0,0,0,0,0,0l0,20H140z">
            </path>
        </symbol>
    </svg>
    <div class="box">
        <div class="percent">
            <div class="percentNum" id="count">0</div>
            <div class="percentB" id="sign">%</div>
        </div>
        <div id="water" class="water">
            <svg viewBox="0 0 560 20" class="water_wave water_wave_back">
                <use xlink:href="#wave"></use>
            </svg>
            <svg viewBox="0 0 560 20" class="water_wave water_wave_front">
                <use xlink:href="#wave"></use>
            </svg>
        </div>
    </div>
    <!-- <div><input type="number" id="level"></div> -->
</body>

</html>

<script>
    var cnt = document.getElementById("count");
    var percentSign = document.getElementById("sign");
    var water = document.getElementById("water");
    var percent = cnt.innerText;

    InitWebSocket()
    function InitWebSocket()
        {
            websock = new WebSocket('ws://'+window.location.hostname+':81/');
            websock.onmessage = function(evt)
        {
            JSONobj = JSON.parse(evt.data);
            let percent = JSONobj.percentage
            cnt.innerHTML = percent;
            water.style.transform = 'translate(0' + ',' + (100 - percent) + '%)';

                if (percent <= 15) {
                    cnt.style.color = "red";
                    percentSign.style.color = "red";
                }   
                else if(percent >= 85) {
                    cnt.style.color = "rgb(113, 235, 52)";
                    percentSign.style.color = "rgb(113, 235, 52)";
                }

                else {
                    cnt.style.color = "white";
                    percentSign.style.color = "white";
                }

        }
    }

</script>


<!-- https://codepen.io/ElaineXu/pen/jrzGrw -->




)=====";
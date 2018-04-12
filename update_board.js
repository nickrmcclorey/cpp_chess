var board = document.getElementById('gameboard');

    function createPattern() {
      // creating the checker pattern on the board
      for (k=1; k<9; k=k+2) {
        for (i=1; i<9; i=i+2) {
          board.rows[k].cells[i].style.background="white";
          board.rows[k].cells[i+1].style.background="#e72e2e";
        }// of first inner for

        for (i=1; i<9; i=i+2) {
          board.rows[k+1].cells[i+1].style.background="white";
          board.rows[k+1].cells[i].style.background="#e72e2e";

        }// of second inner loop
      }// of outer for
    }
    createPattern();


function clearBoard() {

}

function updateBoard(board_info) {


  // clear the board
  for (var k = 1; k < 9; k++) {
    for (var i = 1; i < 9; i++) {
      board.rows[k].cells[i].innerHTML = "";
    }
  }

  // update board with info from json file
  for (var k = 0; k < board_info.pieces.length; k++) {

    // get x and y position
    xpos = board_info.pieces[k].xPos;
    ypos = board_info.pieces[k].yPos;

    // adjust x and y position for the html table
    xpos++;
    ypos++;

    // put it on the board
    board.rows[9-ypos].cells[xpos].innerHTML = '<img src="chessPics/'+board_info.pieces[k].team+board_info.pieces[k].type+'.png"</img>';

  }
}

  // variable that gets the json data
  var request = new XMLHttpRequest();
  request.onreadystatechange = function() {

    // checks to see if it was succesful
    if (this.readyState == 4 && this.status == 200) {

      // contains all the info from the json file
      var board_info = JSON.parse(this.responseText);
      //updates the board with variable containing all info
      updateBoard(board_info);

    }
  }

// responsible for calling the function to update data
document.addEventListener("click",function(){  request.open("GET", "saved_games/current.json", true);
  request.send();},false);

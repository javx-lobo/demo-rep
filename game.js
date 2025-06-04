const logEl = document.getElementById('log');
const startBtn = document.getElementById('startBtn');

function log(msg) {
  logEl.textContent += msg + '\n';
  logEl.scrollTop = logEl.scrollHeight;
}

// Data for cards and tiles
const cardNumbers = ['2','3','4','5','6','7','8','9','10','J','Q','K','A'];
const suits = ['\u2660','\u2663','\u2666','\u2665'];

const tileKinds = ['suits','honors','bonus'];
const tileNumbers = ['1','2','3','4','5','6','7','8','9'];
const winds = ['e-wind','s-wind','n-wind','w-wind','w-dragon','g-dragon','r-dragon'];
const bonuses = ['winter','spring','autumn','summer','plum','chrysanthemum','bamboo','orchid'];

function random(arr){ return arr[Math.floor(Math.random()*arr.length)]; }
function dice(){ return Math.floor(Math.random()*12)+1; }

function rShot(){
  const names = ["0","1-red","2-black","3-red","4-black","5-red","6-black","7-red","8-black","9-red","10-black","12-red","11-black","14-red","13-black","16-red","15-black","18-red","17-black","19-red","20-black","21-red","22-black","23-red","24-black","25-red","26-black","27-red","28-black","30-red","29-black","32-red","31-black","34-red","33-black","36-red","35-black","0"];
  const n = Math.floor(Math.random()*38);
  return {number:n, name:names[n]};
}

function drawCard(){
  return {number: random(cardNumbers), suit: random(suits)};
}

function drawTile(){
  const kindId = Math.floor(Math.random()*3);
  if(kindId===0){
    return {kind:'suits', suit: random(['dots','bamboos','characters']), name: random(tileNumbers)};
  } else if(kindId===1){
    const isWind = Math.random()<0.5;
    if(isWind){
      const val = Math.floor(Math.random()*4);
      return {kind:'honors', suit:'winds', name:winds[val]};
    } else {
      const val = Math.floor(Math.random()*3)+4;
      return {kind:'honors', suit:'dragons', name:winds[val]};
    }
  } else {
    const isSeason = Math.random()<0.5;
    const val = Math.floor(Math.random()*4);
    if(isSeason){
      return {kind:'bonus', suit:'seasons', name:bonuses[val]};
    } else {
      return {kind:'bonus', suit:'flowers', name:bonuses[val+4]};
    }
  }
}

function checkHand(cards){
  const values = cards.map(c=>cardNumbers.indexOf(c.number));
  values.sort((a,b)=>a-b);
  const suitsSame = cards.every(c=>c.suit===cards[0].suit);
  if(suitsSame){
    if(values[0]===9 && values[1]===10 && values[2]===11 && values[3]===12) return 900+values[0]*5; // prez flush
    if(values[0]===values[1]-1 && values[1]===values[2]-1 && values[2]===values[3]-1) return 800+values[0]*5; // four flush
    return 600+values[3]*5; // lepto flush
  } else {
    if(values[0]===values[1] && values[1]===values[2] && values[2]===values[3]) return 700+values[0]*5; // poker
    if(values[0]===values[1]-1 && values[1]===values[2]-1 && values[2]===values[3]-1) return 500+values[0]*5; // four rank
    if((values[0]===values[1] && values[1]===values[2]) || (values[1]===values[2] && values[2]===values[3])) return 400+values[1]*5; // triplet
    if(values[0]===values[1] && values[2]===values[3]) return 300+values[3]*5; // doublets
    if(values[0]===values[1] || values[1]===values[2] || values[2]===values[3]){
      if(values[0]===values[1]) return 200+values[0]*5;
      if(values[1]===values[2]) return 200+values[1]*5;
      return 200+values[2]*5;
    }
    return 100+values[3]*5; // hi card
  }
}

function windsCheck(tiles){
  for(const t of tiles){
    if(t.kind==='honors' && t.suit==='winds'){
      switch(t.name){
        case 'e-wind': return 1;
        case 's-wind': return 2;
        case 'n-wind': return 3;
        case 'w-wind': return 4;
      }
    }
  }
  return 0;
}

function fspCheck(tiles){
  let wnum=0,nnum=0,dnum=0,snum=0,fnum=0;
  for(const t of tiles){
    if(t.kind==='honors' && t.suit==='winds'){ wnum++; }
  }
  if(wnum>=2) return 0; // too many winds
  let dlen = 5-wnum;
  for(const t of tiles){ if(t.kind==='suits') nnum++; }
  if(dlen===4){ if(nnum>=3) return 0; dlen-=nnum; }
  else if(nnum>3){ return 0; } else { dlen-=nnum; }
  for(const t of tiles){ if(t.kind==='honors' && t.suit==='dragons') dnum++; }
  if(dlen===5){ if(dnum===2||dnum===3) dlen-=dnum; else return 0; }
  else if(dlen===4){ if(dnum===1||dnum===2) dlen-=dnum; else return 0; }
  else if(dlen===3){ if(dnum===0||dnum===1) dlen-=dnum; else return 0; }
  else { if(dnum===0) dlen-=dnum; else return 0; }
  for(const t of tiles){ if(t.kind==='bonus' && t.suit==='seasons') snum++; else if(t.kind==='bonus') fnum++; }
  if(fnum===0 || snum===0) return 1; else return 0;
}

function jellyBean(player){
  const bean = Math.floor(Math.random()*3);
  let guess = parseInt(prompt(`Player ${player+1}, choose a hand (0=Left,1=Center,2=Right)`));
  if(guess===bean){ log('Bingo!'); return true;} else { log('Oh no! Nothing there!'); return false; }
}

function startGame(){
  logEl.textContent='';
  let gold = parseInt(prompt('Select initial player gold:', '100')) || 100;
  const players = [
    {gold, dominance:18, position:0, rwin:0},
    {gold, dominance:36, position:1, rwin:0}
  ];
  let win=0,round=0,fspwin=0,ibet=0;

  while(!win){
    round++;
    log(`--- Round ${round} ---`);
    const cards = players.map(()=>Array.from({length:4},drawCard));
    const tiles = players.map(()=>Array.from({length:5},drawTile));
    const handScores = cards.map(c=>checkHand(c));

    for(let i=0;i<2;i++){
      log(`Player ${i+1} cards:`);
      cards[i].forEach(c=>log(` ${c.number}${c.suit}`));
      const score=handScores[i];
      players[i].handscore=score;
      if(score>=900) log(`Player ${i+1} has a Prez Flush`);
      else if(score>=800) log(`Player ${i+1} has a Four Flush`);
      else if(score>=700) log(`Player ${i+1} has a Poker`);
      else if(score>=600) log(`Player ${i+1} has a Lepto Flush`);
      else if(score>=500) log(`Player ${i+1} has a Four Rank`);
      else if(score>=400) log(`Player ${i+1} has a Triplet`);
      else if(score>=300) log(`Player ${i+1} has Doublets`);
      else if(score>=200) log(`Player ${i+1} has a Pair`);
      else log(`Player ${i+1} has Hi-Card`);
    }

    // Bets
    ibet=0;
    for(let i=0;i<2;i++){
      let bet=parseInt(prompt(`Player ${i+1} place your bet:`,'0'))||0;
      if(bet>players[i].gold) bet=players[i].gold;
      players[i].gold-=bet;
      ibet+=bet;
    }

    // deck winner prediction
    let dwin=0;
    if(players[0].handscore>players[1].handscore){log('Player 1 would win the deck.');dwin=1;}
    else if(players[1].handscore>players[0].handscore){log('Player 2 would win the deck.');dwin=2;}
    else{log('It\'s a draw, find another way.');}

    // show tiles and winds
    for(let i=0;i<2;i++){
      log(`Player ${i+1} tiles:`);
      tiles[i].forEach(t=>log(` ${t.name} of ${t.suit}`));
    }
    for(let i=0;i<2;i++){
      const w= windsCheck(tiles[i]);
      if(w){
        log(`Player ${i+1} has the ${['East','South','North','West'][w-1]} Wind`);
        if((w===1||w===2)&&players[i].position===0 || (w===3||w===4)&&players[i].position===1){
          if(confirm(`Player ${i+1}, switch seats?`)){
            const other=i===0?1:0;
            [players[i].position,players[other].position]=[players[other].position,players[i].position];
            if(dwin===i+1) dwin=other+1; else if(dwin===other+1) dwin=i+1;
            log(`Players switched seats.`);
          }
        } else {
          log(`But Player ${i+1} can't move that way.`);
        }
      } else {
        log(`Player ${i+1} has no winds.`);
      }
    }

    // Dice and roulette
    const diceVal = dice();
    log(`Dice rolled ${diceVal}`);
    if(diceVal%2===0){
      log('Even number. No roulette.');
    } else {
      log('Odd number. Spinning roulette...');
      const rou=rShot();
      log(`Roulette shows ${rou.name}`);
      if(rou.number===0 || rou.number===37){
        log('Zero. Nothing happens.');
      } else if(rou.number%2===1){
        if(rou.number<=players[0].dominance){ log('Red number in Player 1 dominance. +10% gold'); players[0].gold+=players[0].gold*0.1; }
        else { log('Red number in Player 2 dominance. +10% gold'); players[1].gold+=players[1].gold*0.1; }
      } else {
        if(rou.number<=players[0].dominance){ log('Black number in Player 1 dominance. Player 1 loses.'); players[1].gold+=players[0].gold+ibet; players[0].gold=0; win=2; players[1].rwin++; }
        else { log('Black number in Player 2 dominance. Player 2 loses.'); players[0].gold+=players[1].gold+ibet; players[1].gold=0; win=1; players[0].rwin++; }
      }
    }

    // FSP
    if(!win){
      const fsp = tiles.map(t=>fspCheck(t));
      if(fsp[0] && fsp[1]){
        log('Both players have an FSP! Rolling dice...');
        const fd = dice();
        if(fd%2===0){ log('Player 1 goes first.'); if(jellyBean(0)){win=1;players[0].rwin++;fspwin=1;} else if(jellyBean(1)){win=2;players[1].rwin++;fspwin=1;} }
        else { log('Player 2 goes first.'); if(jellyBean(1)){win=2;players[1].rwin++;fspwin=1;} else if(jellyBean(0)){win=1;players[0].rwin++;fspwin=1;} }
      } else if(fsp[0]){ log('Player 1 has an FSP.'); if(jellyBean(0)){win=1;players[0].rwin++;fspwin=1;} }
      else if(fsp[1]){ log('Player 2 has an FSP.'); if(jellyBean(1)){win=2;players[1].rwin++;fspwin=1;} }
      else { log('Nobody has an FSP.'); }
    }

    // Deck comparison and bet retribution
    if(!win){
      log('No winner yet. Deck decides.');
      if(dwin===1){ players[0].gold+=ibet; log('All bets to Player 1'); }
      else if(dwin===2){ players[1].gold+=ibet; log('All bets to Player 2'); }
      else { log('Draw. Bets remain on table.'); }
    }
  }

  // Rewards
  const winner = win-1;
  const loser = win===1?1:0;
  log(`Player ${winner+1} wins!`);
  players[winner].gold+=50;
  if(players[loser].rwin<=3){ players[winner].gold+=100; log('Clear Diamond!'); }
  if(players[loser].rwin===0){ players[winner].gold+=400; log('Colored Diamond!'); }
  if(round<=9){ players[winner].gold+=200; log('Ruby Ankh!'); }
  if(round<=6){ players[winner].gold+=800; log('Golden Ankh!'); }
  if(round<=3){ players[winner].gold+=1600; log('Platinum Ankh!'); }
  if(fspwin){ players[winner].gold+=3200; log('Rhodium Jewel!'); }
  if(players[loser].rwin===0 && fspwin && round<=3){ players[winner].gold*=2; log('Relic of Perfection!!!'); }
  log(`Winner's gold: ${players[winner].gold}`);
}

startBtn.addEventListener('click', startGame);

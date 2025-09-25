// Implementations translated from the C++ attachments

// Utility
const $ = id => document.getElementById(id);

function isLetter(c){return /[A-Za-z]/.test(c)}

// --- Caesar ---
function caesarEncrypt(text, key){
  key = ((key%26)+26)%26;
  return Array.from(text).map(c=>{
    if(/[A-Z]/.test(c)) return String.fromCharCode((c.charCodeAt(0)-65+key)%26+65);
    if(/[a-z]/.test(c)) return String.fromCharCode((c.charCodeAt(0)-97+key)%26+97);
    return c;
  }).join('');
}
function caesarDecrypt(text,key){return caesarEncrypt(text,-key)}

// --- Affine ---
function egcd(a,b){if(b===0) return {g:a,x:1,y:0}; let r=egcd(b,a%b); return {g:r.g,x:r.y,y:r.x-Math.floor(a/b)*r.y}}
function modInverse(a,m){a=((a%m)+m)%m; for(let x=1;x<m;x++){if((a*x)%m===1) return x} return -1}
function affineEncrypt(text,a,b){
  return Array.from(text).map(c=>{
    if(/[A-Z]/.test(c)){
      return String.fromCharCode(((a*(c.charCodeAt(0)-65)+b)%26)+65);
    }
    if(/[a-z]/.test(c)){
      return String.fromCharCode(((a*(c.charCodeAt(0)-97)+b)%26)+97);
    }
    return c;
  }).join('');
}
function affineDecrypt(text,a,b){
  const a_inv = modInverse(a,26);
  if(a_inv===-1) return 'ERROR: a has no modular inverse (gcd(a,26) != 1)';
  return Array.from(text).map(c=>{
    if(/[A-Z]/.test(c)){
      let y=c.charCodeAt(0)-65; let dec=(a_inv*(y-b+26))%26; return String.fromCharCode(dec+65);
    }
    if(/[a-z]/.test(c)){
      let y=c.charCodeAt(0)-97; let dec=(a_inv*(y-b+26))%26; return String.fromCharCode(dec+97);
    }
    return c;
  }).join('');
}

// --- Permutation (Hoán vị) ---
function permutationEncrypt(text,key){
  const n=key.length; let t=text;
  while(t.length % n !== 0) t += 'X';
  let res='';
  for(let i=0;i<t.length;i+=n){
    const block=t.slice(i,i+n);
    let newBlock=Array(n).fill(' ');
    for(let j=0;j<n;j++) newBlock[j]=block[key[j]-1];
    res+=newBlock.join('');
  }
  return res;
}
function permutationDecrypt(text,key){
  const n=key.length; let res='';
  for(let i=0;i<text.length;i+=n){
    const block=text.slice(i,i+n);
    let newBlock=Array(n).fill(' ');
    for(let j=0;j<n;j++) newBlock[key[j]-1]=block[j];
    res+=newBlock.join('');
  }
  return res;
}

// --- Playfair ---
function generateKeyMatrix(key){
  key = key.toUpperCase().replace(/[^A-Z]/g,'').replace(/J/g,'I');
  const used = Array(26).fill(false);
  let arr=[];
  for(const ch of key){
    const idx=ch.charCodeAt(0)-65; if(!used[idx]){used[idx]=true; arr.push(ch)}
  }
  for(let c=0;c<26;c++){
    const ch=String.fromCharCode(65+c); if(ch==='J') continue; if(!used[c]){used[c]=true; arr.push(ch)}
  }
  const matrix=[]; for(let i=0;i<5;i++) matrix.push(arr.slice(i*5,i*5+5));
  return matrix;
}
function findPosition(matrix,ch){
  if(ch==='J') ch='I'; ch=ch.toUpperCase();
  for(let i=0;i<5;i++) for(let j=0;j<5;j++) if(matrix[i][j]===ch) return [i,j];
  return [-1,-1];
}
function prepareTextPlayfair(text){
  text = text.toUpperCase().replace(/[^A-Z]/g,'').replace(/J/g,'I');
  let res='';
  for(let i=0;i<text.length;i++){
    res+=text[i];
  }
  let prepared='';
  for(let i=0;i<res.length;i+=2){
    let a=res[i]; let b=res[i+1];
    if(!b){prepared+=a+'X'; break}
    if(a===b){prepared+=a+'X'; i--; continue}
    prepared+=a+b;
  }
  if(prepared.length%2===1) prepared+= 'X';
  return prepared;
}
function playfairEncrypt(text,matrix){
  const prepared=prepareTextPlayfair(text);
  let out='';
  for(let i=0;i<prepared.length;i+=2){
    const a=prepared[i], b=prepared[i+1];
    const [r1,c1]=findPosition(matrix,a); const [r2,c2]=findPosition(matrix,b);
    if(r1===r2){ out+=matrix[r1][(c1+1)%5]; out+=matrix[r2][(c2+1)%5]; }
    else if(c1===c2){ out+=matrix[(r1+1)%5][c1]; out+=matrix[(r2+1)%5][c2]; }
    else { out+=matrix[r1][c2]; out+=matrix[r2][c1]; }
  }
  return out;
}
function playfairDecrypt(text,matrix){
  let out='';
  for(let i=0;i<text.length;i+=2){
    const a=text[i], b=text[i+1];
    const [r1,c1]=findPosition(matrix,a); const [r2,c2]=findPosition(matrix,b);
    if(r1===r2){ out+=matrix[r1][(c1+4)%5]; out+=matrix[r2][(c2+4)%5]; }
    else if(c1===c2){ out+=matrix[(r1+4)%5][c1]; out+=matrix[(r2+4)%5][c2]; }
    else { out+=matrix[r1][c2]; out+=matrix[r2][c1]; }
  }
  return out;
}

// --- Vigenere ---
function vigenereEncrypt(text,key){
  key = key.replace(/[^A-Za-z]/g,''); if(!key) return text;
  let ki=0; let out='';
  for(const ch of text){
    if(/[A-Z]/.test(ch)){
      const k = key[ki%key.length].toUpperCase().charCodeAt(0)-65;
      out += String.fromCharCode((ch.charCodeAt(0)-65 + k)%26 + 65); ki++;
    } else if(/[a-z]/.test(ch)){
      const k = key[ki%key.length].toLowerCase().charCodeAt(0)-97;
      out += String.fromCharCode((ch.charCodeAt(0)-97 + k)%26 + 97); ki++;
    } else out += ch;
  }
  return out;
}
function vigenereDecrypt(text,key){
  key = key.replace(/[^A-Za-z]/g,''); if(!key) return text;
  let ki=0; let out='';
  for(const ch of text){
    if(/[A-Z]/.test(ch)){
      const k = key[ki%key.length].toUpperCase().charCodeAt(0)-65;
      out += String.fromCharCode((ch.charCodeAt(0)-65 - k + 26)%26 + 65); ki++;
    } else if(/[a-z]/.test(ch)){
      const k = key[ki%key.length].toLowerCase().charCodeAt(0)-97;
      out += String.fromCharCode((ch.charCodeAt(0)-97 - k + 26)%26 + 97); ki++;
    } else out += ch;
  }
  return out;
}

// --- UI wiring ---
const params = $('params'); const inputText = $('inputText'); const outputText = $('outputText');
const encryptBtn = $('encryptBtn'); const decryptBtn = $('decryptBtn'); const clearBtn = $('clearBtn');
const tabs = document.querySelectorAll('.tab'); const matrixContainer = $('matrixContainer');

let activeCipher = 'caesar';
function setActiveCipher(name){
  activeCipher = name;
  tabs.forEach(t=>t.classList.toggle('active', t.dataset.cipher===name));
  renderParams();
}

function renderParams(){
  const v = activeCipher; params.innerHTML=''; matrixContainer.innerHTML=''; matrixContainer.style.display='none';
  if(v==='caesar'){
    params.innerHTML = `<label>Key (số): <input id="caesarKey" type="number" value="3"></label>`;
  } else if(v==='affine'){
    params.innerHTML = `<label>a: <input id="affineA" type="number" value="5"></label> <label>b: <input id="affineB" type="number" value="8"></label>`;
  } else if(v==='playfair'){
    params.innerHTML = `<label>Key (chuỗi): <input id="playfairKey" type="text" value="KEYWORD"></label>`;
    matrixContainer.style.display='block';
    matrixContainer.setAttribute('aria-hidden','false');
    // render live matrix for default key
    const input = document.createElement('input'); input.id='playfairKey'; input.type='text'; input.value='KEYWORD'; input.style.display='none'; // hidden duplicate so parse works
    params.appendChild(input);
    renderPlayfairMatrix('KEYWORD');
    // attach handler to visible param later via event delegation
  } else if(v==='permutation'){
    params.innerHTML = `<label>Key (1-based, space separated): <input id="permKey" type="text" value="3 1 4 2"></label>`;
  } else if(v==='vigenere'){
    params.innerHTML = `<label>Key (chuỗi): <input id="vigKey" type="text" value="LEMON"></label>`;
  }
}

tabs.forEach(t=>t.addEventListener('click', ()=> setActiveCipher(t.dataset.cipher)));
setActiveCipher('caesar');

// Update matrix when playfair key changes (listen on params container)
params.addEventListener('input', (e)=>{
  if(activeCipher==='playfair'){
    const el = params.querySelector('#playfairKey');
    if(el) renderPlayfairMatrix(el.value||'');
  }
});

function renderPlayfairMatrix(key){
  try{
    const matrix = generateKeyMatrix(key||'');
    matrixContainer.innerHTML = '<div class="matrix"><div class="label">Playfair matrix</div>' +
      matrix.flat().map(ch=>`<div class="cell">${ch}</div>`).join('') + '</div>';
  }catch(e){ matrixContainer.innerHTML = '<div class="label">Invalid key</div>' }
}

function parsePermKey(val){
  const parts = val.trim().split(/\s+/).filter(Boolean).map(x=>parseInt(x,10));
  if(parts.some(p=>isNaN(p))) throw new Error('Invalid permutation key');
  return parts;
}

encryptBtn.addEventListener('click', ()=>{
  try{
  const v=activeCipher; const txt=inputText.value;
    let out='';
    if(v==='caesar'){ const k = parseInt($('caesarKey').value || '0',10); out = caesarEncrypt(txt,k) }
    else if(v==='affine'){ const a = parseInt($('affineA').value,10); const b = parseInt($('affineB').value,10); out = affineEncrypt(txt,a,b) }
    else if(v==='playfair'){ const key = $('playfairKey').value || ''; const m = generateKeyMatrix(key); out = playfairEncrypt(txt,m) }
    else if(v==='permutation'){ const k = parsePermKey($('permKey').value); out = permutationEncrypt(txt,k) }
    else if(v==='vigenere'){ const k=$('vigKey').value||''; out = vigenereEncrypt(txt,k) }
    outputText.value = out;
  }catch(e){outputText.value = 'ERROR: '+e.message}
});

decryptBtn.addEventListener('click', ()=>{
  try{
  const v=activeCipher; const txt=inputText.value;
    let out='';
    if(v==='caesar'){ const k = parseInt($('caesarKey').value || '0',10); out = caesarDecrypt(txt,k) }
    else if(v==='affine'){ const a = parseInt($('affineA').value,10); const b = parseInt($('affineB').value,10); out = affineDecrypt(txt,a,b) }
    else if(v==='playfair'){ const key = $('playfairKey').value || ''; const m = generateKeyMatrix(key); out = playfairDecrypt(txt,m) }
    else if(v==='permutation'){ const k = parsePermKey($('permKey').value); out = permutationDecrypt(txt,k) }
    else if(v==='vigenere'){ const k=$('vigKey').value||''; out = vigenereDecrypt(txt,k) }
    outputText.value = out;
  }catch(e){outputText.value = 'ERROR: '+e.message}
});

clearBtn.addEventListener('click', ()=>{inputText.value=''; outputText.value=''});

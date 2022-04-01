import React,{useEffect} from "react"
const AuthProcess = () => {
    
    const REACT_APP_CLIENT_ID = '5333d45d4adc40bb804c41a285300cdb'
    const REACT_APP_AUTHORIZE_URL = "https://accounts.spotify.com/authorize"
    const REACT_APP_REDIRECT_URL = "http://localhost:3000/ok"
    var scope = '';
    const generateRandomString = function(length) {
        var text = '';
        var possible = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
      
        for (var i = 0; i < length; i++) {
          text += possible.charAt(Math.floor(Math.random() * possible.length));
        }
        return text;
    };
    useEffect(()=>{
        handleLogin();
    })
    var state = generateRandomString(16);
    var url = 'https://accounts.spotify.com/authorize';
        url += '?response_type=token';
        url += '&client_id=' + encodeURIComponent(REACT_APP_CLIENT_ID);
        url += '&scope=' + encodeURIComponent(scope);
        url += '&redirect_uri=' + encodeURIComponent(REACT_APP_REDIRECT_URL);
        url += '&state=' + encodeURIComponent(state);
    const handleLogin = () => {
        window.location = url;
    };
    return(
        <div>
        </div>
    )
    
}
export default AuthProcess;
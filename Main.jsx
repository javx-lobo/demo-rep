import React from "react";
import {BrowserRouter as Router ,Link,Route, Redirect} from "react-router-dom";
import logo from "../assets/img/logo.png";

const Main = () =>
{
    const refresh = () => {
      localStorage.removeItem('token')
    }
    return(
        
        <div className="App">
      <header className="App-header">

        <Link to="/login">
        <img src={logo} className="App-logo" onClick={refresh} alt="logo" />
        </Link>
        <h1>
          Start browsing Spotify.
        </h1>
        <p>
          Just click on the big green logo to begin.
        </p>
      </header>
</div>
    )

}

export default Main
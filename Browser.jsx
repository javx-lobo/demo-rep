import React, {useEffect, useState} from "react";
import logo from "../assets/img/logo.png";
import noimg from "../assets/img/no-image.png"
import axios from "axios";

const Browser = () => {
    const [emptyState, setEmptyState] = useState(false)
    const [token, setToken] = useState('')
    const [mode, setMode] = useState("album")
    const [query, setQuery] = useState("");
    const [response, setResponse] = useState([]);
    
    const browse = async (e) =>{
        
        e.preventDefault()
        
        const {data} = await axios.get(
            "https://api.spotify.com/v1/search", {
            headers: {
                Authorization: `Bearer ${token}`
            },
            params: {
                q: query,
                type: mode
            }
        }
            )
            .catch((err) => {
                if(err.message || err.request || err.response){
                    setEmptyState(true)
                }
                
            } )

        switch (mode) {
            case "artist":
                setResponse(data.artists.items)
                break;
            case "album":
                setResponse(data.albums.items)
                break;
            case "track":
                setResponse(data.tracks.items);
                break;
        }
             
    }
useEffect(() => {
    
    const hash = window.location.hash
    let token = window.localStorage.getItem("token")

    if (!token && hash) {
        token = hash.substring(1).split("&").find(elem => elem.startsWith("access_token")).split("=")[1]

        window.location.hash = ""
        window.localStorage.setItem("token", token)
    }

    setToken(token)

}, [])

   const popCheck = (pop) => {
        var key = Math.round(pop*0.05);
        var stars = ""
        switch (key) {
            case 0:
                stars = "⭐"
                break;
            case 1:
                stars = "⭐"
                break;
            case 2:
                stars = "⭐⭐"
                break;
            case 3:
                stars = "⭐⭐⭐"
                break;
            case 4:
                stars = "⭐⭐⭐⭐"
                break;
            case 5:
                stars = "⭐⭐⭐⭐⭐"
                break;
        }
        return stars
    } 

    const fetchGenres = (genreArray) =>{
        var genreString = ""
        if(genreArray && genreArray.length != 0){
        genreArray.forEach(element => {
            genreString += element.charAt(0).toUpperCase() + element.slice(1) + ", ";
            });
        }
        else{
            genreString = "Unknown"
        }
        return genreString
    }
        
    const renderResponse = () => {
    return response.map(res => (
        <div className="elements" key={res.id}>
            <img src={
                    res.images ?
                        res.images.length ?
                        res.images[0].url :
                        noimg
                        : noimg
                } />
            <h2>{res.name}</h2>
            <h3>{   res.type === "album" ?
                    "By " + res.artists[0].name
                    : "Popularity: " + popCheck(res.popularity)}
            </h3>
            <p>{ mode === "artist" ?
                     "Genres: " + fetchGenres(res.genres) :
                        res.release_date?
                        "Release Year: " + res.release_date.substring(0,4):
                        "Release Year: Unknown"
                     }
                </p>
        </div>
        
    ))
    }
        
    return(
        
        <div>
            <header>
            <div><img src={logo} alt="spotlogo" /></div>
            <div><h1>Spotify Browser</h1></div>
            <nav>
                <div>
                <form onSubmit={browse}>
         <input placeholder={"Search " + mode} onChange={e => setQuery(e.target.value)} />
         <button className="search" type={'submit'}>🔎</button>
                </form>
                </div>
                <div>
                    <button className=
                        {mode == "album" ? "active" : ""} 
                        onClick={() => setMode("album")}>Albums
                    </button>
                    <button className=
                    {mode == "artist" ? "active" : ""} 
                    onClick={() => setMode("artist")}>Artists
                    </button>
                    <button className=
                    {mode == "track" ? "active" : ""} 
                    onClick={() => setMode("track")}>Tracks</button>
                </div>
                
            </nav>
        </header>
        {/* <h2 className={emptyState && query != "" || response.length == 0 && query != "" ? "show" : "hide"}>Nothing to see here.</h2> */}
        <h2 className={!emptyState && query == "" || !emptyState && !query ? "show" : "hide"}>Please introduce a query</h2>
        <main>
            {renderResponse()}
        </main> 
        </div>
    )
}

export default Browser
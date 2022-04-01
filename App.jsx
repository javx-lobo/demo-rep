import React from 'react';
import {BrowserRouter as Router,Routes,Route, Redirect} from "react-router-dom";
import './App.scss';
import AuthProcess from './components/auth3';
import Main from './components/Main';
import Browser from './components/Browser';

function App() {
  return (
    <Router>
    <Routes>
      <Route path="/" element={<Main />} />
      <Route path="/login" element={<AuthProcess />} />
      <Route path="/ok" element={<Browser />} />
    </Routes>
    </Router>
  );
}

export default App;

import React from 'react';
import './First.css';
import backgroundVideo from '../../video/backgroundVideo1.mp4';

const First = () => {
  const handleMenuToggle = () => {
    const menuToggle = document.querySelector('.toggle');
    const showcase = document.querySelector('.showcase');
    menuToggle.classList.toggle('active');
    showcase.classList.toggle('active');
  };

  const sendCommandToArduino = (command) => {
    console.log('Button clicked:', command); // Добавлен console.log
    fetch('http://127.0.0.1:8000/api/control_arduino/', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ data: command }), // Заменить "command" на "data"
    })
    .then(response => response.json())
    .then(data => {
      if (data.success) {
        console.log('Command sent successfully');
      } else {
        console.error('Failed to send command');
      }
    })
    .catch(error => {
      console.error('Error:', error);
    });
  };
  

  return (
    <>
      <section className="showcase">
        <header>
          <h2 className="logo">Аудиоплеер</h2>
          <div className="toggle" onClick={handleMenuToggle}></div>
        </header>
        <video src={backgroundVideo} muted loop autoPlay></video>
        <div className="overlay"></div>
        <div className="text">
          <button className="button pause-play" onClick={() => sendCommandToArduino('p')}></button>
          <button className="button next" onClick={() => sendCommandToArduino('n')}></button>
          <button className="button previous" onClick={() => sendCommandToArduino('b')}></button>
          <button className="button volumeUp" onClick={() => sendCommandToArduino('u')}></button>
          <button className="button volumeDown" onClick={() => sendCommandToArduino('d')}></button>
        </div>
        <ul className="social">
          <li><a href="https://www.facebook.com/?locale=ru_RU"><img src="https://i.ibb.co/x7P24fL/facebook.png" alt="Facebook"/></a></li>
          <li><a href="https://twitter.com/?lang=ru"><img src="https://i.ibb.co/Wnxq2Nq/twitter.png" alt="Twitter"/></a></li>
          <li><a href="https://www.instagram.com/erkosho1/"><img src="https://i.ibb.co/ySwtH4B/instagram.png" alt="Instagram"/></a></li>
        </ul>
      </section>
      <div className="menu">
        <ul>
          <li><a href="#">Первый</a></li>
          <li><a href="#">Второй</a></li>
          <li><a href="#">Третий</a></li>
        </ul>
      </div>
    </>
  );
};

export default First;

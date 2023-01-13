
<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GPL License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Mez0ry/SnakeGame-SDL">
    <img src="https://img.freepik.com/free-vector/cute-snake-branch-cartoon-vector-icon-illustration-animal-nature-icon-concept-isolated-premium-vector-flat-cartoon-style_138676-4188.jpg?w=740&t=st=1671781340~exp=1671781940~hmac=ea6c2ed168b9278f71d8b7f14452c742ea77584032a25a956d80886552f96cba" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">SnakeGame-SDL</h3>

  <p align="center">
    SnakeGame-SDL is a cross-platform game written using SDL,SDL_image,SDL_ttf, SDL_mixer
    <br />
    <a href="https://github.com/Mez0ry/SnakeGame-SDL"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Mez0ry/SnakeGame-SDL">View Demo</a>
    ·
    <a href="https://github.com/Mez0ry/SnakeGame-SDL/issues">Report Bug</a>
    ·
    <a href="https://github.com/Mez0ry/SnakeGame-SDL/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

SnakeGame-SDL - is a cross-platform game written using SDL, it also has things like achievements, different types of food and they are divided into edible and inedible, there is a fully clickable game menu, as well as a config file in which you can adjust screen resolution and map size,if you have played a couple of matches and you really want to see the score of previous games, you can also look at the statistics by clicking on «Match history» in the game menu

<p align="right">(<a href="#readme-top">back to top</a>)</p>


### Built With

* [![SDL][SDL]][SDL-url]
* [![SDLImage][SDLImage]][SDL_Image-url]
* [![SDL_ttf][SDL_ttf]][SDL_ttf-url]
* [![SDL_mixer][SDL_mixer]][SDL_mixer-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Below are the simple steps  to get a local copy up, and to run it.
Follow these simple example steps and you should be fine.

### Prerequisites

This header describes the steps to be taken before building

#### &emsp;Linux

* installing SDL_mixer dependencies
  ```sh
     cd SnakeGame-SDL/vendor/SDL_mixer/external/
     ./download.sh
  ```
#### &emsp;Windows
* installing SDL_mixer dependencies
 ```sh
     cd SnakeGame-SDL/vendor/SDL_mixer/external/
     sh download.sh
  ```
  If you have problems with this read this article [StackOverflow article](https://stackoverflow.com/questions/26522789/how-to-run-sh-on-windows-command-prompt)  
  
### Build
1. Clone the repo
   ```sh
   git clone https://github.com/Mez0ry/SnakeGame-SDL
   ```
2. Building
#### &emsp;Linux
   ```sh
   cd SnakeGame-SDL
   mkdir build && cd build && cmake ..
   make
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the GPL-3.0 License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Mez0ry - [@discord](https://discord.gg/YDm3zR8yWh) - mez0ry.dev@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Mez0ry/SnakeGame-SDL.svg?style=for-the-badge
[contributors-url]: https://github.com/Mez0ry/SnakeGame-SDL/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Mez0ry/SnakeGame-SDL.svg?style=for-the-badge
[forks-url]: https://github.com/Mez0ry/SnakeGame-SDL/network/members
[stars-shield]: https://img.shields.io/github/stars/Mez0ry/SnakeGame-SDL.svg?style=for-the-badge
[stars-url]: https://github.com/Mez0ry/SnakeGame-SDL/stargazers
[issues-shield]: https://img.shields.io/github/issues/Mez0ry/SnakeGame-SDL.svg?style=for-the-badge
[issues-url]: https://github.com/Mez0ry/SnakeGame-SDL/issues
[license-shield]: https://img.shields.io/github/license/Mez0ry/SnakeGame-SDL.svg?style=for-the-badge
[license-url]: https://github.com/Mez0ry/SnakeGame-SDL/blob/master/LICENSE.txt
[product-screenshot]: images/screenshot.png
[SDL]: https://img.shields.io/badge/SDL-a9f743?style=for-the-badge&logo=data%3Aimage%2Fjpeg%3Bbase64%2C%2F9j%2F4AAQSkZJRgABAQAAAQABAAD%2F2wBDAAwICAgJCAwJCQwRCwoLERUPDAwPFRgTExUTExgRDAwMDAwMEQwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAz%2F2wBDAQ0LCw0ODRAODhAUDg4OFBQODg4OFBEMDAwMDBERDAwMDAwMEQwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAz%2FwAARCABQAFADASIAAhEBAxEB%2F8QAHAAAAgIDAQEAAAAAAAAAAAAABQYDBwACBAEI%2F8QAMhAAAQMDBAECAwcEAwAAAAAAAQIDBAAFEQYSITEHE0EiI1EVMjZCYXHwJTM1UnKR4f%2FEABgBAAMBAQAAAAAAAAAAAAAAAAABAgME%2F8QAIxEAAgIBAwQDAQAAAAAAAAAAAAECEQMhMUESEyJRMlJhcf%2FaAAwDAQACEQMRAD8Ad9T6tt%2BnmAqQrc4ofC2O6VIvl%2BEXsPtEIJ7pMv0qVqzUaUM5PAbH0HNFrl4nuMW3mS06HHEJ3FH1rrjixRSU35Mm3wWDddcWy3W1m4HLjbwBSE890EHmCykj5S6VLw05H0lHZfQUOtpwpKqF2TQtxvNvVOjqASn8p7NEcOLpbl7qwtl02HUluvjHqxFgnsozyK4tT60g6dWhElJUV9YqotLXGZpvUSEu5RlXpOJJOO6afLakPNRJCOlpGansJZEt4yHehY1ivLF6gImxwQ2voGiNK3jcY0yx%2FPammsJpKTS4YzRS9pGeq2BzzWrqN6CmoIcgOgoxhSODUgfP1mui7FexJWjISv4gfpmrusmrrLekJQy8kvKHxNH9qrbyRo6TDmfaENsqilHx4ySCKSYU2Vb5KZEdRbdR713SxxzRUk6ZN0Wl5dbbagNemkJ3EZx70S8UEmwqB63Us6vvIvekYbyv76EgufvTL4n%2FAMEr%2FlWck1gp7qQciz5ZgNRbtFmMpCdx%2BZj65rj1hLMrT0NZOSMCjXmEjayPfIpWvgWNNxd3%2BwrTFrHG%2FTB8lo%2BOPwyx%2FPammlbxx%2BGWP57U01yZfnL%2BlLYyhj0xiNcAx0txO6idC7yIzYS8vAczgKPdShPYmiTbbeYpW0UvsklJB56qu%2FJ2k7dGhi4RUpaczykcA0l2HV14068pMdR2FWVNrqfUWs7tqQoirHwZ%2BFCeya64YJwnafiK7RGFOHThznGKsrxRhNgUonA3Up6itCbPo%2BH6o2uvpAUDwcml2060vdohKhQ3AllffHNVKLywaj9g2YzeVLkxPvMSHHWFhs4Xt55JqHW0Mw7BDbUME4OKF6Ls0rUOoEvP7loQfVWs8gnPVMvl7Y2mKwjgISBihVGePGuNw9sbfHGBpljn%2BYpoBB6r57tmuL9a4oixXglpPQxVi%2BMtT3W9uSUT3AsNjKaxzYJLqnaqxplgUq60trspLTrbpTsUPhBppPAzSVcL4LjqT7IaSoemncrP6VlC7tcIU%2Fiye9%2BOLPcnPVbSGnMYJFRWPxpa7ZKTJc%2BatByjPtTpWUd2dV1OiqAGqbTZ7iw2zciEtp%2B6TwBS6jQuidycPoUe9uRzTheLMxdWg2990UHjaEgsPBzeVY4AyeKIzklSk0B0Wd7S9raLMJTbW3hQ4zxXLfrfpa%2FpDkyQgFHRyKlVoa3FZWMhROc5rRzQlvWnbuP%2FAHR1a3bv2ALR4%2B0cpkOhxOw%2FmyKOaWsFjtPqqtTiXCvhZSc1qdHsCMmOhwhCfbNd9msce0IWGj9%2Fkk0OcmqcmwO%2BRJZjtlbywhIHZpbs8SNPvTl3bTgBJbCvrz3Uesf6oyi3w3PmKUN23%2Fyj9ngIt8BmOntKRuP60to76sh%2BUq4jud1eV7WVJZ4FA9V7Ua28g7eCajW682BxmgDorK5HLg22sJIPNQOXVQk%2BkhGU4zk%2FWnTFaCJUACScAUAuF8bmokW%2BAo%2BsUlG8exNbpYu0qStTqwI6hgJFd0CzQ4WVNoG9XJV75p6L9Ym29Fp%2Bg%2FTen%2Fs9gLkrLr57Uruj9ZWUm23bGkktD%2F%2FZ&logoColor=df0
[SDL-url]: https://www.libsdl.org/

[SDLImage]: https://img.shields.io/badge/SDL_Image-ffd500?style=for-the-badge&logo=&logoColor=ffd500
[SDL_Image-url]: https://github.com/libsdl-org/SDL_image
[SDL_ttf]: https://img.shields.io/badge/SDL_ttf-f80?style=for-the-badge&logo=&logoColor=f80
[SDL_ttf-url]: https://github.com/libsdl-org/SDL_ttf
[SDL_mixer]: https://img.shields.io/badge/SDL_mixer-FF3E00?style=for-the-badge&logo=&logoColor=FF3E00
[SDL_mixer-url]: https://github.com/libsdl-org/SDL_mixer

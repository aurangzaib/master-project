$(function () {
  $.get("https://api.listnride.com/v2/featured", function (a) {
    $.get("https://code.getmdl.io/1.2.1/material.indigo-pink.min.css", function () {
      a.forEach(function (a) {
        $("#listnride").append(
          '<div class="mdl-cell mdl-cell--4-col mdl-cell--middle"><div class="lnr-card-wide mdl-card mdl-shadow--2dp"><div class="mdl-card__media"><img src="' +
          a.image_file_1.image_file_1.small.url +
          '" width="100%" height="80%"></div><div class="mdl-card__supporting-text">' + a.brand + ", " +
          a.category + "</div></div></div>");
      });
    });
  });
});


<?php 
require_once 'stripe-php-master/init.php';


require_once 'config.php'; 


?>
<!DOCTYPE html>
<html>
	<head><title>Develo - Diseño, Desarrollo y Negocio Digital</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="../css/bootstrap.css">
<link rel="shortcut icon" href="../images/favicon.png">
<link rel="stylesheet" href="../css/jquery-ui.css">
<script src="../scripts/jquerybase.js"></script>
<script src="../scripts/jquery-ui.js"></script>
  <script src="https://js.stripe.com/v2/"></script>
  <link rel="stylesheet" href="../css/StripeElements.css">
	</head>
	<body>
	
<link rel="stylesheet" href="../css/externo.css">

<header id="main-header">
<nav id="nav-wrapper">
	<div id="nav-head" class="subpage">
	<a href="../index.html"><img id="logo-top" src="../images/develo-logo.png"></a>
		<ul>
			
			<a href="diseno-audiovisual.html"><li id="diseno">Diseño Audiovisual
				<ul id="flyout-1">
					<a href="diseno-audiovisual.html#musica"><li>Mezcla y Creación Musical</li></a>
					<a href="diseno-audiovisual.html#videos"><li>Edición de Videos</li></a>
					<a href="diseno-audiovisual.html#juegos"><li>Diseño de Videojuegos</li></a>
					<a href="diseno-audiovisual.html#graficos"><li>Gráficos y Artwork</li></a>
				</ul></li></a>
			<a href="desarrollo-web.html"><li id="desarrollo">Desarrollo Web
				<ul id="flyout-2">
					<a href="desarrollo-web.html#web"><li>Mi Sitio Web</li></a>
					<a href="desarrollo-web.html#apps"><li>Aplicaciones Web</li></a>
					<a href="desarrollo-web.html#cms"><li>CMS Management</li></a>
					<a href="desarrollo-web.html#seo"><li>SEO y Optimización</li></a>
				</ul></li></a>
				<a href="ebooks-y-contenido.html"><li id="contenido">Ebooks y Contenido
				<ul id="flyout-3">
					<a href="ebooks-y-contenido.html#guiones"><li>Guiones y Screenplays</li></a>
					<a href="ebooks-y-contenido.html#ebooks"><li>Edición y Publicación de Ebooks</li></a>
					<a href="ebooks-y-contenido.html#creacion-contenido"><li>Creación de Contenido</li></a>
					<a href="ebooks-y-contenido.html#traduccion"><li>Servicios de Traducción</li></a>
				</ul></li></a>
			<li id="blogfor"><a href="users.php">Productos</a></li>
			<li id="about"><a href="about.html">Conócenos</a></li>
			<li id="t-burger"><button>☰</button></li>
				<ul id="flyout-4">
					<a href="diseno-audiovisual.html"><li id="sub-diseno">Diseño Audiovisual
						<ul id="flyout-5">
							<a href="diseno-audiovisual.html#musica"><li>Mezcla y Creación Musical</li></a>
							<a href="diseno-audiovisual.html#videos"><li>Edición de Videos</li></a>
							<a href="diseno-audiovisual.html#juegos"><li>Diseño de Videojuegos</li></a>
							<a href="diseno-audiovisual.html#graficos"><li>Gráficos y Artwork</li></a>
						</ul>
					</li></a>
					<a href="desarrollo-web.html"><li id="desarrollo"><li id="sub-desarrollo">Desarrollo Web
						<ul id="flyout-6">
							<a href="desarrollo-web.html#web"><li>Mi Sitio Web</li></a>
							<a href="desarrollo-web.html#apps"><li>Aplicaciones Web</li></a>
							<a href="desarrollo-web.html#cms"><li>CMS Management</li></a>
							<a href="desarrollo-web.html#seo"><li>SEO y Optimización</li></a>
						</ul>
					</li></a>
					<a href="ebooks-y-contenido.html"><li id="sub-contenido">Ebooks y Contenido
						<ul id="flyout-7">
							<a href="ebooks-y-contenido.html#guiones"><li>Guiones y Screenplays</li></a>
							<a href="ebooks-y-contenido.html#ebooks"><li>Edición y Publicación de Ebooks</li></a>
							<a href="ebooks-y-contenido.html#creacion-contenido"><li>Creación de Contenido</li></a>
							<a href="ebooks-y-contenido.html#traduccion"><li>Servicios de Traducción</li></a>
						</ul></a>
					</li>
					<li><a href="users.php">Productos</a></li>
					<li><a href="about.html">Conócenos</a></li>
				</ul>
		</ul>
	</div>
</nav>
</header>


<div id="supercontainer">
	<div id="mid-section" class="subpage_ms">
	<div id="title-segment">
		<h1 id="subpage-title">Completa tu Pedido</h1>
	</div>
	<section id="displaya" class="container">
		<section class="row">
<div class="card mt-4 mb-4">
    <form action="payment.php" method="POST" id="paymentFrm">
        <div class="card-header">
            <h3 class="card-title">Suscripción y pagos</h3>
			
        </div>
        <div class="card-body">
            
            <div class="card-errors"></div>
			
           
            <div class="form-group form-row">
                <label class="badge-pill">NOMBRE</label>
                <input type="text" class="form-control" name="name" id="name" placeholder="Introduce nombre" required="" autofocus="">
            </div>
            <div class="form-group form-row">
                <label class="badge-pill">EMAIL</label>
                <input type="email" class="form-control" name="email" id="email" placeholder="Introduce email" required="">
            </div>
            <div class="form-group form-row">
                <label class="badge-pill">NÚMERO DE TARJETA</label>
                <input type="text" class="form-control" name="card_number" id="card_number" placeholder="1234 1234 1234 1234" maxlength="16" autocomplete="off" required="">
            </div>
            <div class="row">
                <div class="left col">
                    <div class="form-group form-row">
                        <label class="badge-pill">FECHA CADUCIDAD</label>
						<div class="form-row">
                        <div class="col-2 mr-4">
                            <input class="form-control" type="text" name="card_exp_month" id="card_exp_month" placeholder="MM" maxlength="2" required="">
                        </div>
                        <div class="col-4">
                            <input class="form-control" type="text" name="card_exp_year" id="card_exp_year" placeholder="AAAA" maxlength="4" required="">
                        </div>
						</div>
                    </div>
                </div>
                <div class="right col">
                    <div class="form-group form-row">
                        <label class="badge-pill">CVC</label>
                        <input type="text" class="form-control" name="card_cvc" id="card_cvc" placeholder="CVC" maxlength="3" autocomplete="off" required="">
                    </div>
                </div>
            </div>
            <button type="submit" class="btn btn-success" id="payBtn">Pagar</button>
        </div>
    </form>
</div>
</section>
	</section>
	</div>
</div>


<footer id="main-footer">
	<div id="follow-us">
		<p>Síguenos</p>
		<ul>
			<li><a target="_blank" href="https://gab.com/Develo"><img src="../images/follow-proto.png"></a></li>
			<!-- <li><img src="../images/follow-alfa.png"></li> -->
		</ul>
	</div>
	<hr width="80%">
	<div id="mid-footer">
		<div id="mf-clearfix">
			<div id="we-three-sections">
				<div class="widzmin">
					<h5>Nuestros Servicios</h5>
					<ul>
						<li><a href="diseno-audiovisual.html">Diseño Audiovisual</a></li>
						<li><a href="desarrollo-web.html">Desarrollo Web</a></li>
						<li><a href="ebooks-y-contenido.html">Ebooks y Contenido</a></li>
						<li><a href="users.php">Productos</a></li>
					</ul>
				</div>
				<div class="widzmin">
					<h5>Contáctanos</h5>
					<ul>
						<li><a href="mailto:info@develo.club" id="info-email">📧 info@develo.club</a></li>
						<li><a href="tel:+34689157985">📱 946 369 927</a></li>
						<li><a href="tel:+34689157985">💬 689 157 985</a></li>
					</ul>
				</div>
				<div class="widzmin">
					<h5>Información Legal</h5>
					<ul>
						<li><a href="politica.html"> Política de Privacidad</a></li>
						<li><a href="aviso.html">Aviso Legal</a></li>
					</ul>
				</div>
			</div>
			<div id="pasta-senpai">
				<a href="../index.html"><img id="logo-footer" src="../images/develo-logo.png"></a>
				
			</div>
		</div>
	</div>
	<div id="small-footer">
	</div>
</footer>
<script>
document.addEventListener('scroll', function () {
if($("#nav-wrapper").offset().top!=0){
$("#nav-head").removeClass("subpage");
$("#nav-head").css({"transition":"all .6s ease","background-color":"#694588","color":"#A6C05A"});
$("#logo-top").attr("src","../images/develo-logo-sat.png");
}
else{
$("#nav-head").addClass("subpage");
$("#nav-head").css({"background-color":"initial","color":"#FFFDC6"});
$("#logo-top").attr("src","../images/develo-logo.png");}
}, true)
$("#t-burger").on("click",function(){
if($(window).width()<901){
$("#flyout-4").toggleClass("ttnow");
}});
//LISTAS JQ-FIX
$("#diseno").on("mouseover",function(){
$("#flyout-1").css({"visibility":"visible","opacity":"1"})
$("#flyout-2").css({"visibility":"hidden","opacity":"0"})
$("#flyout-3").css({"visibility":"hidden","opacity":"0"})
})
$("#diseno ul").on("mouseout",function(){
$("#flyout-1").css({"visibility":"hidden","opacity":"0"})
})
$("#desarrollo").on("mouseover",function(){
$("#flyout-2").css({"visibility":"visible","opacity":"1"})
$("#flyout-1").css({"visibility":"hidden","opacity":"0"})
$("#flyout-3").css({"visibility":"hidden","opacity":"0"})
})
$("#desarrollo ul").on("mouseout",function(){
$("#flyout-2").css({"visibility":"hidden","opacity":"0"})
})
$("#contenido").on("mouseover",function(){
$("#flyout-3").css({"visibility":"visible","opacity":"1"})
$("#flyout-2").css({"visibility":"hidden","opacity":"0"})
$("#flyout-1").css({"visibility":"hidden","opacity":"0"})
})
$("#contenido ul").on("mouseout",function(){
$("#flyout-3").css({"visibility":"hidden","opacity":"0"})
})





Stripe.setPublishableKey('pk_test_wja5YgBYaDPPBeEim0LGm98y00kA9ZKo7T');
function stripeResponseHandler(status, response) {
    if (response.error) {
  
        $('#payBtn').removeAttr("disabled");
  
        $(".payment-status").html('<p>'+response.error.message+'</p>');
    } else {
        var form$ = $("#paymentFrm");
   
        var token = response.id;
		localStorage.token=token;
       
        form$.append("<input type='hidden' name='stripeToken' value='" + token + "' />");
      
        form$.get(0).submit();
    }
}

$(document).ready(function() {
  
    $("#paymentFrm").submit(function() {
     
        $('#payBtn').attr("disabled", "disabled");
		
      
        Stripe.createToken({
            number: $('#card_number').val(),
            exp_month: $('#card_exp_month').val(),
            exp_year: $('#card_exp_year').val(),
            cvc: $('#card_cvc').val()
        }, stripeResponseHandler);
		
      
        return false;
    });
});
</script>
</body>
</html>
from selenium import webdriver 
# import org.openqa.selenium.firefox.FirefoxDriver;
from selenium.webdriver.support.ui import WebDriverWait 
from selenium.webdriver.support import expected_conditions as EC 
from selenium.webdriver.common.keys import Keys 
from selenium.webdriver.common.by import By 
from selenium.common.exceptions import WebDriverException
import time 
import pyperclip
import random
import pandas
import os
import ctypes
ctypes.windll.kernel32.SetConsoleTitleW("LinkedSnake Legacy")
import numpy
import sys
import math
from colorama import init
init()
from colorama import Fore, Back, Style
sys.ps1 = "\033[1;35m>>>\033[0m "
sys.ps2 = "\033[1;32m...\033[0m "
import getpass


# argos = str(sys.argv)
# argi = argos.split(',')


print("\033[35m*************************\n")
print("|| \033[32mLINKED SNAKE LEGACY \033[35m||\n")
print("*************************\n\033[36m")
sysrnd = random.SystemRandom()
# The Human Serpent Behavior Generator
level = sysrnd.randint(5,99)
powp = sysrnd.randrange(5,130,2)
dfc = sysrnd.randrange(5,162,3)
snakewords = input("Dile algo a la serpiente: ")
primalSerpent = sysrnd.randint(int.from_bytes(snakewords.encode(),'little'), sysrnd.randrange(0,int.from_bytes(snakewords.encode(),'big')**2)) 
baseSerpent = primalSerpent + ((primalSerpent + level)/32) * ((primalSerpent * level)/32)
maxSerpent = ((powp * (512-dfc) * baseSerpent) / (16 * 512))
humanSerpent = maxSerpent*(3841*sysrnd.randint(0,255))/4096
random.seed(round(humanSerpent))
target = input("Introduce tu email de LinkedIn: ")
string = getpass.getpass("Introduce tu contraseña de LinkedIn: ")
url = input("Introduce el slug del perfil a inspeccionar: ")
comp = bool(input("¿Es un perfil de empresa? Si no lo es, no pongas nada y dale a enter: "))
if comp:
	inn = "/company/"
	tail = ""
else:
	inn = "/in/"
	tail = "/detail/recent-activity/shares/"
maxcount=int(input("Introduce el número de scrolls que quieres hacer: "))
# Replace below path with the absolute path 
# to chromedriver in your computer CHECK
# driver = webdriver.Chrome(executable_path=r'C:\\Users\\Asier\\Documents\\javlib\\py\\chromedriver.exe')
# Or use Mozilla
driver = webdriver.Firefox(executable_path=r''+os.getcwd()+'/geckodriver.exe')


driver.get("https://linkedin.com/") 

wait = WebDriverWait(driver, 600) 
fuse = WebDriverWait(driver, 15) 


fedora = "//*[contains(text(), 'Iniciar sesión')]"
# fedora2 = "//*[contains(text(), 'Iniciar sesión')]"
skipper = '//button[@class="secondary-action"]'
xar = '//input[@id="username"]'
seer = '//input[@id="password"]'

# if location.href == "https://www.linkedin.com/signup/cold-join?session_redirect=https%3A%2F%2Fwww%2Elinkedin%2Ecom%2Fin%2Fjackie-chun-09566a1b1%2Fdetail%2Frecent-activity%2Fshares%2F&trk=login_reg_redirect"
	
indiana=wait.until(EC.presence_of_element_located(( 
	By.XPATH, fedora))) 
indiana.click()
lurk = wait.until(EC.presence_of_element_located(( 
	By.XPATH, xar))) 
locate = wait.until(EC.presence_of_element_located(( 
	By.XPATH, seer)))
 
time.sleep(sysrnd.uniform(0.5115,1.023)*5)
lurk.click() 
time.sleep(sysrnd.uniform(0.5115,1.023)*5)
lurk.send_keys(target + Keys.ENTER)
time.sleep(sysrnd.uniform(0.5115,1.023)*5)
locate.click()
time.sleep(sysrnd.uniform(0.5115,1.023)*5)
locate.send_keys(string + Keys.ENTER)
time.sleep(sysrnd.uniform(0.5115,1.023)*5)

# fedora = "//*[contains(text(), 'Inicia sesión')]"
# indiana=wait.until(EC.presence_of_element_located(( 
	# By.XPATH, fedora))) 

driver.get('https://www.linkedin.com'+inn+url+tail)

print(Fore.YELLOW + "Haciendo scroll...")

count = 0
while (count < maxcount-1):
    driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
    time.sleep(sysrnd.uniform(1,5.115))
    count = count + 1

print(Fore.YELLOW + "Buscando publicaciones...")

ariadivs = []
ariadivs = driver.find_elements_by_css_selector("div[class*='feed-shared-update-v2 feed-shared-update-v2--minimal-padding full-height relative']")
if comp:
	del ariadivs[1:2]
# ariadivs = driver.find_elements_by_xpath("//div[@class='feed-shared-update-v2__control-menu absolute text-align-right feed-shared-control-menu ember-view']")


print("La serpiente ha encontrado "+str(len(ariadivs))+" publicaciones.")
calctime = str(math.ceil((8.65*(len(ariadivs)))/60))
print("Recolectando datos más importantes de las publicaciones... (Si quieres, vuelve en unos "+calctime+" minutos)")
print("Puedes comprobar la consola de Linked Snake Legacy de vez en cuando para comprobar el progreso del proceso, pero por favor, no maximices la ventana del navegador Firefox una vez la hayas minimizado, o el proceso terminará abruptamente.")
saves = pandas.DataFrame(columns=['Titulo','Link','Reacciones'])
braker = 0 # check notifications
stale=True
for ariadiv in ariadivs:
	driver.execute_script("arguments[0].scrollIntoView(true); window.scrollBy(0, -180);", ariadiv)
	time.sleep(sysrnd.uniform(0.5115,1.023)*2.4)

	# Search for: 1) Button & copy
	ariabutton = ariadiv.find_element_by_css_selector('button[class="feed-shared-control-menu__trigger artdeco-button artdeco-button--tertiary artdeco-button--muted artdeco-button--1 artdeco-button--circle artdeco-dropdown__trigger artdeco-dropdown__trigger--placement-bottom ember-view"]')
	ariabutton.click()
	time.sleep(sysrnd.uniform(0.5,1.023))
	try:
		listitem = ariadiv.find_element_by_css_selector('li[class*="option-share-via"]')
		listitem.click()
	except:
		print("Entrando en Excepción 1")
		try:
			listitem = ariadiv.find_element_by_xpath('//li[contains(@class,"option-share-via")]')
			listitem.click()
		except:
			print("Entrando en Excepción 2")
			while stale:
				print("Entrando en bucle")
				ariabutton = ariadiv.find_element_by_css_selector('button[class="feed-shared-control-menu__trigger artdeco-button artdeco-button--tertiary artdeco-button--muted artdeco-button--1 artdeco-button--circle artdeco-dropdown__trigger artdeco-dropdown__trigger--placement-bottom ember-view"]')
				ariabutton.click()                                                                                                                                                     
				try:
					listitem = ariadiv.find_element_by_css_selector('li[class*="option-share-via"]')
					listitem.click()
					stale=False
				except:
					print("Entrando en Excepción 3")
					try:
						ariadivs = driver.find_elements_by_css_selector("div[class*='feed-shared-update-v2 feed-shared-update-v2--minimal-padding full-height relative']")
						listitem = ariadiv.find_element_by_xpath('//li[contains(@class,"option-share-via")]')
						listitem.click()
						stale=False
					except:
						print("An error has ocurred. Let's try something else.")
						saves.to_excel("post-links.xlsx",index=False)
						driver.execute_script("alert('Imprimido lo que teníamos');") #Revisar, jump needed to saves
	finally:
		
		# saves.append(pyperclip.paste())  In development, probably id will become the value, changing the key (title) & self.value (likes) every for-lap
		time.sleep(sysrnd.uniform(0.8,1.623))
		
		# Search for: 2) Title
		ariaitem1 = ariadiv.find_element_by_css_selector('div[class="feed-shared-text relative feed-shared-update-v2__commentary  ember-view"]')
		ariatitle=ariaitem1.text
		ariatitle = ariatitle[:25]
		time.sleep(sysrnd.uniform(0.8,2.023))
		
		# Search for: 3) Reactions given
		try:
			ariaitem2 = ariadiv.find_element_by_css_selector('span[class="v-align-middle social-details-social-counts__reactions-count"]')
			arialyx = int(ariaitem2.text)
		except:
			arialyx = 0
		
		time.sleep(sysrnd.uniform(0.5,1.523))
		  
		
		# Finally paste into a dataframe
		saves= saves.append({'Titulo':ariatitle, 'Link':pyperclip.paste(), 'Reacciones':arialyx},ignore_index=True)
		saves = saves.sort_values(by=['Reacciones'], ascending=False)
		completion=float(len(saves))/float(len(ariadivs))
		
		# Progression Check 4 the user
		if completion == 1:
			print("Se acabó! La serpiente ha terminado su trabajo.")
		elif completion >=0.97 and braker ==9:
			print("Ya está por el "+str(round(completion*100))+"%, sólo un poco más de paciencia...")
			braker+=1
		elif completion >=0.88 and braker ==8:
			print("Estamos en la recta final, el "+str(round(completion*100))+"% de las publicaciones ya han sido recolectadas.")
			braker+=1
		elif completion >=0.76 and braker ==7:
			print("¡Tres cuartos completados! Ya tenemos el "+str(round(completion*100))+"% de las publicaciones.")
			braker+=1
		elif completion >=0.65 and braker ==6:
			print("La serpiente ha obtenido ya el "+str(round(completion*100))+"% de las publicaciones.")
			braker+=1
		elif completion >=0.54 and braker ==5:
			print("Más de la mitad completado, el "+str(round(completion*100))+"% de las publicaciones ya han sido recolectadas.")
			braker+=1
		elif completion >=0.42 and braker ==4:
			print("Casi a medio camino, el "+str(round(completion*100))+"% de las publicaciones ya han sido recolectadas.")  
			braker+=1
		elif completion >=0.33 and braker ==3:
			print("Un tercio de las publicaciones ya han sido recolectadas por la serpiente, concretamente el "+str(round(completion*100))+"%.")
			braker+=1
		elif completion >=0.25 and braker ==2:
			print("Un cuarto completado, el "+str(round(completion*100))+"% de las publicaciones ya han sido recolectadas.")
			braker+=1
		elif completion >=0.14 and braker ==1:
			print("¿Sigues ahí? Si es así, que sepas que el "+str(round(completion*100))+"% de las publicaciones ya han sido recolectadas.")
			braker+=1
		elif completion >= 0.08 and braker ==0:
			print("La serpiente lleva un "+str(round(completion*100))+"% de publicaciones recolectadas")
			braker+=1
	
	



saves.to_excel(""+url+".xlsx",index=False)

driver.execute_script("alert('Todo imprimido');")


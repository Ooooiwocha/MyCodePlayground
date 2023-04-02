#USE IT AT YOUR OWN RISK

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import os;
import time


url = input("input community url");
driver = webdriver.Chrome();
##driver.maximize_window();
driver.get(url);
dir = url.split("/")[-2];
os.makedirs(dir, exist_ok=True);
wait = WebDriverWait(driver, 20);
wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, 'yt-formatted-string[id^="published-time-text"]')));

for _ in range(100):
	driver.execute_script("window.scrollBy(0, 2147483547);");
	time.sleep(0.0625);

##print(driver.find_element(By.TAG_NAME, ("html")).text)
arr = driver.find_elements(By.CSS_SELECTOR, 'div[id="post"]');
for elem in arr:
	##print("elem.text: " + elem.text)
	date = elem.find_element(By.CSS_SELECTOR, 'yt-formatted-string[id^="published-time-text"]');
	postlink = date.find_element(By.TAG_NAME, 'a').get_attribute("href")
	print(postlink);

	driver.execute_script("window.open();")
	driver.switch_to.window(driver.window_handles[1])
	driver.get(postlink);

	WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.CSS_SELECTOR, 'a[id^="author-text"]')))

	for _ in range(100):
		driver.execute_script("window.scrollBy(0, 1000);");
		wait.until(EC.presence_of_all_elements_located((By.CSS_SELECTOR, 'div[id^="body"]')))
		time.sleep(0.0025);
	try:
		commentsection = driver.find_element(By.CSS_SELECTOR, 'ytd-item-section-renderer[id^="sections"]');
	except Exception as e:
		msg = driver.find_elements(By.CSS_SELECTOR, 'yt-formatted-string[id="message"]');
		if len(msg): ## continue if comment section is turned off
			driver.execute_script("window.close();")
			driver.switch_to.window(driver.window_handles[0]);
			continue; 
		print(e);
		exit();
	buttons = commentsection.find_elements(By.CSS_SELECTOR, 'ytd-button-renderer[id^="more-replies-icon"]');

	for button in buttons:
		button = button.find_element(By.TAG_NAME, "button");
		driver.execute_script("arguments[0].click();", button);
		
		##button.click() <- this method is troublesome!! 

	driver.execute_script("window.scrollTo(0, 0);");
	height = driver.execute_script("return document.documentElement.scrollHeight");
	print("height: ", height)

	for i in range(0, height, 150):
		driver.execute_script("window.scrollTo(0, {});".format(i));
		time.sleep(0.0625)

	driver.find_element(By.TAG_NAME, "body").send_keys(Keys.END);
	wait.until(EC.presence_of_all_elements_located((By.CSS_SELECTOR, 'div[id^="body"]')))
	time.sleep(1.5)

	commentsection = driver.find_element(By.CSS_SELECTOR, 'ytd-item-section-renderer[id^="sections"]');
	comments = commentsection.find_elements(By.CSS_SELECTOR, 'div[id^="body"]');

	##print([t.text for t in comments]);

	with open(dir + "/" + postlink.split("/")[-1] + ".txt", mode="w", encoding="utf-8") as f:	
		for comment in comments:
			print(comment.location);
			author_name = comment.find_element(By.CSS_SELECTOR, 'a[id^="author-text"]');
			comment_id = comment.find_element(By.CSS_SELECTOR, 'yt-formatted-string[class^="published-time-text"]').find_element(By.TAG_NAME, "a");
			comment_content = comment.find_element(By.CSS_SELECTOR, 'yt-formatted-string[id^="content-text"]');
			row = "\t".join([author_name.text, comment_content.text.replace("\r\n", " ").replace("\n", " "), comment_id.get_attribute("href")]) + "\r\n";
			print(row);
			f.write(row);

	driver.execute_script("window.close();")
	driver.switch_to.window(driver.window_handles[0]);

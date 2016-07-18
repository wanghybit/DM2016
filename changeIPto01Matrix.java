package DNS_Mining;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class test {

	public static void main(String[] args) throws IOException, FileNotFoundException {
		// TODO Auto-generated method stub
		File file = new File("G://GH//Data Mining//project//会话数据");
		File[] list = file.listFiles();
		for(int s = 0 ; s <list.length;s++){
			File CSession1 = new File(list[s].getAbsolutePath());
			String result_path = "G://GH//Data Mining//project//Session_for_clementine//"+list[s].getName()+".txt";
			OutputStreamWriter out = new OutputStreamWriter(
					new FileOutputStream(result_path), "UTF-8");
			FileReader f_reader;
			int count = 0;
			Set<String> IP = new HashSet<String>();
			ArrayList<String> example = new ArrayList<String>();
			ArrayList<String> IP_list = new ArrayList<String>();
			try {
				f_reader = new FileReader(CSession1);
				BufferedReader b_reader = new BufferedReader(f_reader);
				String str = "";
				while ((str = b_reader.readLine()) != null) {
					count++;
					example.add(str);
					String session[] = str.split("\\|");
					// System.out.println(session.length);
					for (int i = 4; i < session.length; i++) {
						IP.add(session[i]);
						// System.out.print(session[i] + "\t");
						// out.write(session[i] + "\t");
					}
					System.out.println();
					// out.write("\r\n");
				}
				// System.out.println(IP.size());
				for (String string : IP) {
					IP_list.add(string);
				}
				for (int i = 0; i < example.size() + 1; i++) {
					if (i == 0) {
						String[] row = new String[IP_list.size()];
						for (int n = 0; n < row.length; n++) {
							row[n] = "0";
						}

						for (int j = 0; j < row.length; j++) {
							row[j] = IP_list.get(j);
							out.write(row[j] + "\t");
						}
						out.write("\r\n");
					} else {
						char[] row = new char[IP.size()];
						for (int n = 0; n < row.length; n++) {
							row[n] = '0';
						}

						String[] current = example.get(i - 1).split("\\|");
						for (int k = 4; k < current.length; k++) {
							for (int m = 0; m < row.length; m++) {
								if (current[k].equals(IP_list.get(m)))
									row[m] = '1';
							}
						}
						for (int a = 0; a < row.length; a++) {
							out.write(row[a] + "\t");
						}
						out.write("\r\n");
					}
					System.out.println("row" + i + "complete");
					out.flush();
				}
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			out.close();
		}

	}

}

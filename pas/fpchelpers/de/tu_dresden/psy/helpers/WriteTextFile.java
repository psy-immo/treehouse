/**
 * WriteTextFile.java, (c) 2013, Immanuel Albrecht; Dresden University of
 * Technology, Professur für die Psychologie des Lernen und Lehrens
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

package de.tu_dresden.psy.helpers;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * 
 * class that covers Write and WriteLn to text files for the free pascal jvm
 * compiler
 * 
 * @author immo
 * 
 */

public class WriteTextFile {
	private File file;
	private BufferedWriter writer;

	private static String newline = System.getProperty("line.separator");

	public WriteTextFile() {
		this.file = null;
		this.writer = null;
	}

	public void Assign(String filename) {
		this.file = new File(filename);
	}

	public void Rewrite() throws IOException {
		this.writer = new BufferedWriter(new FileWriter(this.file));
	}

	public void Append() throws IOException {
		this.writer = new BufferedWriter(new FileWriter(this.file, true));
	}

	public void Write(int x) throws IOException {
		this.writer.write("" + x);
	}

	public void Write(String x) throws IOException {
		this.writer.write(x);
	}

	public void Writeln(int x) throws IOException {
		this.writer.write("" + x + newline);
	}

	public void Writeln(String x) throws IOException {
		this.writer.write(x + newline);
	}

	public void Writeln() throws IOException {
		this.writer.write(newline);
	}

	public void Writeln(String x, int n) throws IOException {
		this.writer.write(x + n + newline);
	}

	public void Close() throws IOException {
		this.writer.close();
		this.writer = null;
	}
}
